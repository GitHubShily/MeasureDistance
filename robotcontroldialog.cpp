#include "robotcontroldialog.h"
#include "ui_robotcontroldialog.h"


RobotControlDialog::RobotControlDialog(QWidget *parent, RobotClient *qRobotClient, CameraControl *qCamera) :
    QDialog(parent),
    ui(new Ui::RobotControlDialog),
    mpRobotClient(qRobotClient),
    mpCamera(qCamera)
{
    ui->setupUi(this);
    connect(&timer,SIGNAL(timeout()),this,SLOT(saveImage()));
	connect(this->ui->figureLabel, SIGNAL(setDistance(float)), this, SLOT(setDistance(float)));
//	connect(this->ui->cameraUpBtn, SIGNAL(pressed()), this, SLOT(cameraUpBtn_pressed()));
//	connect(this->ui->cameraDownBtn, SIGNAL(pressed()), this, SLOT(cameraDownBtn_pressed()));
//	connect(this->ui->cameraLeftBtn, SIGNAL(pressed()), this, SLOT(cameraLeftBtn_pressed()));
//	connect(this->ui->cameraRightBtn, SIGNAL(pressed()), this, SLOT(cameraRightBtn_pressed()));
}

RobotControlDialog::~RobotControlDialog()
{
    delete ui;
    exit(0);
}

void RobotControlDialog::on_robotForwardBtn_clicked()
{
    this->mpRobotClient->goForward();
}

void RobotControlDialog::on_robotBackBtn_clicked()
{
    this->mpRobotClient->goBack();
}

void RobotControlDialog::on_robotLeftBtn_clicked()
{
    this->mpRobotClient->turnLeft();
}

void RobotControlDialog::on_robotRightBtn_clicked()
{
    this->mpRobotClient->turnRight();
}

void RobotControlDialog::on_robotStopBtn_clicked()
{
    this->mpRobotClient->stop();
}

void RobotControlDialog::on_cameraUpBtn_clicked()
{
    mpCamera->cameraMoveUp();
}

void RobotControlDialog::on_cameraDownBtn_clicked()
{
    mpCamera->cameraMoveDown();
}

void RobotControlDialog::on_cameraLeftBtn_clicked()
{
    mpCamera->cameraMoveLeft();
}

void RobotControlDialog::on_cameraRightBtn_clicked()
{
    mpCamera->cameraMoveRight();
}

void RobotControlDialog::on_cameraHomeBtn_clicked()
{
    mpCamera->cameraMoveHome();
}

void RobotControlDialog::on_cameraInBtn_clicked()
{
    mpCamera->cameraZoomIn();
}

void RobotControlDialog::on_cameraOutBtn_clicked()
{
    mpCamera->cameraZoomOut();
}

void RobotControlDialog::on_cameraOpenBtn_clicked()
{

    CameraLoginDialog cameraLogin(0,mpCamera);
    if(cameraLogin.exec()==cameraLogin.Accepted)
    {
        mpCamera->cameraOpen();
        this->timer.start(40);
    }
}

void RobotControlDialog::saveImage()
{
    this->mpCamera->getPixmap();
    this->ui->figureLabel->setmPixmap(this->mpCamera->mPixmap);
    this->ui->figureLabel->resize(this->mpCamera->mPixmap.width(),this->mpCamera->mPixmap.height());
    this->ui->figureLabel->setPixmap(this->mpCamera->mPixmap);
}


void RobotControlDialog::on_cameraStopBtn_clicked()
{
    mpCamera->cameraClose();
    timer.stop();
}

void RobotControlDialog::cameraUpBtn_pressed()
{
	this->mpCamera->cameraMoveUping();
}

void RobotControlDialog::cameraDownBtn_pressed()
{
	this->mpCamera->cameraMoveDowning();
}

void RobotControlDialog::cameraLeftBtn_pressed()
{
	this->mpCamera->cameraMoveLefting();
}

void RobotControlDialog::cameraRightBtn_pressed()
{
	this->mpCamera->cameraMoveRighting();
}

void RobotControlDialog::setDistance(float distance)
{
	this->ui->DistanceValueLabel->setNum(distance);
}
