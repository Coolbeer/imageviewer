#include <QtGui/QPainter>

#include "imageviewer_frontend_qt_new.h"

pwan::imageviewer_frontend_qt_new::imageviewer_frontend_qt_new(int argc, char **argv, QWidget *parent): QApplication(argc, argv), QWidget(parent)
{
}

int pwan::imageviewer_frontend_qt_new::startup(void)
{
    this->show();
    return qApp->exec();
}

void pwan::imageviewer_frontend_qt_new::init(void)
{
    return;
}

void pwan::imageviewer_frontend_qt_new::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,this->geometry().width(), this->geometry().height()), QColor(0,0,0));
}
