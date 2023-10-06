#include "mycoin.h"
#include<QDebug>
#include<QPixmap>
#include<QPushButton>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    //金币背景
    QPixmap pix;
    bool ret =pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("打开图片%1").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer=new QTimer(this);

    //翻转金币
    this->coinFlag();

}

//翻金币
void MyCoin::changeFlag()
{
    if(!this->isAnimaion)
    {
        if(this->flag)  //正面
        {
            timer->start(30);
            this->flag=false;
            this->isAnimaion=true;
        }
        else if(!this->flag)
        {
            timer->start(30);
            this->flag=true;
            this->isAnimaion=true;
        }
    }


}

//翻转
void MyCoin::coinFlag()
{
    connect(timer,&QTimer::timeout,[=](){
    if(!this->flag)
    {

        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            timer->stop();
            this->isAnimaion=false;
        }

    }
    else
    {
        QPixmap pix1;
        QString st=QString(":/res/Coin000%1.png").arg(this->max--);
        pix1.load(st);
        this->setFixedSize(pix1.width(),pix1.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix1);
        this->setIconSize(QSize(pix1.width(),pix1.height()));
        if(this->min>this->max)
        {
            this->max=8;
            timer->stop();
            this->isAnimaion=false;
        }
    }
    });
}

//重写鼠标事件
void MyCoin::mousePressEvent(QMouseEvent *event)
{
    if(this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(event);
    }
}
