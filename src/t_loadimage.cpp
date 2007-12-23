#include "../config.h"
#include "t_loadimage.moc"
#include "t_loadimage.h"

t_loadimage::t_loadimage(QObject *parent) : QThread(parent)
{
	restart = false;
	abort = false;
}

t_loadimage::~t_loadimage(void)
{
	mutex.lock();
	abort = true;
	condition.wakeOne();
	mutex.unlock();
	wait();
}

//void t_loadimage::initialize(void);
//{
void t_loadimage::readimage(std::string filename)
{
	QMutexLocker locker(&mutex);
	fileName.push_back(filename);
#ifdef PWANDEBUG
	std::cout << "Threadimageloader: " << filename << "; Zoom: " << zoom << "\n";
#endif

	if (!isRunning())
		start(LowPriority);
	else
	{
		restart = true;
		condition.wakeOne();
	}
}

void t_loadimage::abortload(void)
{
	QMutexLocker locker(&mutex);
	abort = true;
	restart = true;
	fileName.clear();
}

void t_loadimage::run()
{
	forever
	{
// 		QStringList filename;
		mutex.lock();
		//filename = fileName;
		mutex.unlock();
		while (!fileName.empty())
		{
			image.load(QString().fromStdString(fileName.at(0)));
			emit imagePassDone(image, fileName.at(0));
			mutex.lock();
			fileName.erase(fileName.begin());
			mutex.unlock();
		}
		mutex.lock();
		if (!restart)
			condition.wait(&mutex);
		restart = false;
		mutex.unlock();
	}
}
