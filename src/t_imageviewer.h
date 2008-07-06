#ifndef T_IMAGEVIEWER_H
#define T_IMAGEVIEWER_H

#include <QPaintEvent>
#include <QWidget>

#include "../config.h"
#include "pwanfileinfo.h"

class t_loadimage;

class t_imageviewer : public QWidget
{
    Q_OBJECT

    public:
        t_imageviewer(QWidget *parent = 0);
        bool startimageviewer();

    private:
        std::vector<QImage> imagelist;
        std::vector<int> imagestatuslist;                                               // 0 = not loaded, 1 = loaded, -1 = some error
        void paintEvent(QPaintEvent *);
        bool loadimage(const std::vector<pwan::fileInfo>::iterator& file);
        std::vector<pwan::fileInfo> makeimagelist(std::string path = ".");
        void keyPressEvent(QKeyEvent *keyevent);
        void setupKeys(void);

        t_loadimage *threadloadimage;

        std::vector<std::string> imageformats;
        std::vector<pwan::fileInfo> fileList;
        std::vector<pwan::fileInfo>::iterator index;
        std::string className;
        QPoint imagesize;
        float zoom;
        int imageindex, viewerwidth, viewerheight;
        bool fullscreen, scale;
        int nextImageKey, altNextImageKey, quitImageKey, altQuitImageKey, prevImageKey, altPrevImageKey, firstImageKey;
        int altFirstImageKey, lastImageKey, altLastImageKey, scrollDownImageKey, altScrollDownImageKey;
        int scrollUpImageKey, altScrollUpImageKey, scrollRightImageKey, altScrollRightImageKey, scrollLeftImageKey;
        int altScrollLeftImageKey, zoomOutImageKey, altZoomOutImageKey, zoomInImageKey, altZoomInImageKey;
        int toggleScaleKey, altToggleScaleKey;

    signals:
        void exitprogram(void);

    private slots:
        void imagedone(QImage finishedimage, std::string filename, int imageslot, int imagestatus);
};
#endif
