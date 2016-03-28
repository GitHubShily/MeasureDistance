#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):
    QLabel(parent),
	tracker(true,false,true,true)
{
	//connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateFrame()));
}


void MyLabel::mousePressEvent(QMouseEvent *event)
{
    this->mTopLeft = event->pos();
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
	this->inited = false;
	//mTimer.stop();
    this->mBottomRight = event->pos();

	float x = 0, y = 0, width = 0, height = 0;
	x = mBottomRight.x() < mTopLeft.x() ? mBottomRight.x() : mTopLeft.x();
	y = mBottomRight.y() < mTopLeft.y() ? mBottomRight.y() : mTopLeft.y();
	width = abs(mBottomRight.x() - mTopLeft.x());
	height = abs(mTopLeft.y() - mBottomRight.y());

    if(width>20 && height>20)
    {
        mRect.setTopLeft(mTopLeft);
        mRect.setBottomRight(mBottomRight);

        rect = cv::Rect(x, y, width, height);

		/*if(tracker = Tracker::create("KCF"))
			if (tracker->init(frame, rect))
			{
				//this->mTimer.start(30);
				this->inited = true;
			}
			else
			{
				QMessageBox msbox;
				msbox.setText("tracker init false");
				msbox.exec();
			}
		else
		{
			QMessageBox msbox;
			msbox.setText("algorithm create false");
			msbox.exec();
		}*/
		tracker.init(rect, frame);
		this->inited = true;
    }

}

void MyLabel::updateFrame()
{
	//this->mTimer.stop();
	/*if (this->inited)
		if (tracker->update(frame, rect))
			isRectFount = true;
		else 
		{
			isRectFount = false;
			QMessageBox msbox;
			msbox.setText("frame update false, obj may loss");
			msbox.exec();
		}*/
	//this->mTimer.start();
}

void MyLabel::boundingRect(QRectF rect, bool show)
{
    mRect = rect;
}


void MyLabel::setmPixmap(QPixmap &pixmap)
{
    mPixmap = pixmap;
	mImage = mPixmap.toImage();
	frame = cv::Mat(mImage.height(), mImage.width(), CV_8UC3, const_cast<uchar*>(mImage.bits()), mImage.bytesPerLine());
}
void MyLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);
	painter.setPen(QPen(Qt::red, 2));

	isRectFount = false;

	/*if (this->inited)
		if (tracker->update(frame, rect))
			isRectFount = true;

	if(isRectFount)
		painter.drawRect(rect.x, rect.y, rect.width, rect.height);
	else
		painter.drawRect(0, 0, 0, 0);*/
	if (this->inited)
	{
		rect = tracker.update(frame);
		painter.drawRect(rect.x, rect.y, rect.width, rect.height);
	}

}



