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
void t_loadimage::readimage(std::string filename, int imageslot)
{
	QMutexLocker locker(&mutex);
	fileName.push_back(filename);
    imageslots.push_back(imageslot);

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
    imageslots.clear();
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
            image = QImage(0,0,QImage::Format_Invalid);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextCodec::setCodecForCStrings (codec);
            image.load(QString().fromStdString(fileName.at(0)));
            if(image.isNull())
                emit imagePassDone(image, fileName.at(0), imageslots.at(0), -1);
            else
                emit imagePassDone(image, fileName.at(0), imageslots.at(0));
			mutex.lock();
			fileName.erase(fileName.begin());
            imageslots.erase(imageslots.begin());
			mutex.unlock();
		}
		mutex.lock();
		if (!restart)
			condition.wait(&mutex);
		restart = false;
		mutex.unlock();
	}
}
