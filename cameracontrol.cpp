#include "cameracontrol.h"



CameraControl::CameraControl():
    mpCtrl(std::make_shared<VITAMINDECODERLib::VitaminCtrl>())
{
}

CameraControl::~CameraControl()
{
    if(this->isInited())
        mpCtrl->CloseConnect();
}

QString CameraControl::cameraIp() const
{
    return mCameraIp;
}

void CameraControl::setCameraIp(const QString &cameraIp)
{
    mCameraIp = cameraIp;
}

void CameraControl::cameraOpen()
{
    mpCtrl->SetServerModelType(VITAMINDECODERLib::esrv7KServer);
    mpCtrl->SetUserName(mCameraId);
    mpCtrl->SetPassword(mCameraPassword);
    mpCtrl->SetRemoteIPAddr(mCameraIp);
    mpCtrl->SetCurrentControlCam(1);
    mpCtrl->Connect();
//    QThread::sleep(5);
    mpCtrl->SendCameraCommand("home");
    this->setInited(true);
}

void CameraControl::cameraClose()
{
    mpCtrl->CloseConnect();
    this->setInited(false);
}

void CameraControl::cameraMoveUp()
{
    mpCtrl->SendCameraCommand("up");
}

void CameraControl::cameraMoveDown()
{
    mpCtrl->SendCameraCommand("down");
}

void CameraControl::cameraMoveLeft()
{
    mpCtrl->SendCameraCommand("left");
}

void CameraControl::cameraMoveRight()
{
    mpCtrl->SendCameraCommand("right");
}

void CameraControl::cameraMoveHome()
{
    mpCtrl->SendCameraCommand("home");
}

void CameraControl::cameraZoomIn()
{
    mpCtrl->SendCameraCommand("wide");
    mpCtrl->SendCameraCommand("auto");
}

void CameraControl::cameraZoomOut()
{

    mpCtrl->SendCameraCommand("tele");
}

bool CameraControl::isInited() const
{
    return mInited;
}

void CameraControl::setInited(bool inited)
{
    mInited = inited;
}

void CameraControl::getPixmap()
{    

    QVariant v1,v2;
    mpCtrl->GetSnapshot(VITAMINDECODERLib::ePicFmtJpeg,v1,v2);
    QByteArray bta= v1.toByteArray();
    mPixmap.loadFromData(bta,"jpeg");
}

