#ifndef T_LOADIMAGE_H
#define T_LOADIMAGE_H

#include <QThread>
#include <QMutex>
#include <QImage>
#include <QWaitCondition>
// #include <QStringList>
#include <vector>
#include <string>
#include <iostream>

class t_loadimage : public QThread
{
	Q_OBJECT

	public:
		t_loadimage(QObject *parent = 0);
		~t_loadimage(void);
		void readimage(std::string filename, float zoom = 1.0);
		void abortload(void);

	signals:
		void imagePassDone(const QImage &image, std::string fname, int imageslot = -1);

	protected:
		void run();

	private:
		QWaitCondition condition;
		QMutex mutex;
		QImage image;
		std::vector<std::string> fileName;
		bool restart, abort;
		//int Width, Height;
		float Zoom;
};

#endif
