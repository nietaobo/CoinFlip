#include "mypushbuttion.h"
#include<QDebug>
#include<Qpixmap>
#include<QPropertyAnimation>


MyPushButtion::MyPushButtion(QString normalImg,QString pressing)
{
    this->normalImgPath=normalImg;
    this->pressingPath=pressing;
    QPixmap pix;
    bool ret=pix.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<"打开图片失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButtion::zoom()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    qDebug()<<this->x()<<this->width()<<this->y()<<this->height();
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
