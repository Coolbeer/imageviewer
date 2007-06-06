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
void t_loadimage::readimage(std::string filename, float zoom)
{
	QMutexLocker locker(&mutex);
	fileName.push_back(filename);
#ifdef PWANDEBUG
	std::cout << "Threadimageloader: " << filename << "; Zoom: " << zoom << "\n";
#endif
	Zoom = zoom;
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
		float zoom;
		mutex.lock();
		//filename = fileName;
		zoom = Zoom;
		mutex.unlock();
		while (!fileName.empty())
		{
			image.load(QString().fromStdString(fileName.at(0)));
			if (zoom != 1.0)
				image = image.scaled((int)(float)(image.width()*zoom), (int)((float)image.height()*zoom), Qt::IgnoreAspectRatio, Qt::FastTransformation);
			emit imagePassDone(image, fileName.at(0), zoom);
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
