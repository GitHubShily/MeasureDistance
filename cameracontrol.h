#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H
#include <memory> 
#include <QString>
#include <ActiveQt\QAxWidget>
#include <QGraphicsScene>
#include <QPixmap>
#include <QBitmap>
#include <QByteArray>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>
#include "vitamindecoderlib.h"


class CameraControl
{
public:
    CameraControl();
    ~CameraControl();

    QString cameraIp() const;
    void setCameraIp(const QString &cameraIp);

    void cameraOpen();
    void cameraClose();
    void cameraMoveUp();
    void cameraMoveDown();
    void cameraMoveLeft();
    void cameraMoveRight();
    void cameraMoveHome();

    void cameraZoomIn();
    void cameraZoomOut();

    bool isInited() const;
    void setInited(bool inited);

    void getPixmap();

    QPixmap mPixmap;

private:
    QString mCameraIp = "";
    QString mCameraId = "root";
    QString mCameraPassword = "123456";
    bool  mInited = false;
    std::shared_ptr<VITAMINDECODERLib::VitaminCtrl> mpCtrl;
};

#endif // CAMERACONTROL_H
