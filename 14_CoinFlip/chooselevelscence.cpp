#include "chooselevelscence.h"
#include<QMenuBar>
#include<QPainter>
#include<qDebug>
#include<mypushbuttion.h>
#include<QLabel>
#include<playscene.h>
#include<QSound>

ChooseLevelScence::ChooseLevelScence(QWidget *parent) : QMainWindow(parent)
{
    //4、选择关卡按钮音效
    chooseSound=new QSound(":/res/TapButtonSound.wav",this);

    //5、返回按钮关卡音效
    QSound *backSound=new QSound(":/res/BackButtonSound.wav",this);

    //1、主要场景
    this->setFixedSize(320,580);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar *bar=new QMenuBar(this);
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //2、返回按钮
    MyPushButtion *backBtn=new MyPushButtion(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButtion::clicked,[=](){
        qDebug()<<"点击了";
        backSound->play();
        emit this->choose();

    });

    //3、创建选择关卡的按钮
    this->menuScence();




}

void ChooseLevelScence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}

void ChooseLevelScence::menuScence()
{
    for(int i=0;i<20;i++)
    {
        MyPushButtion *menuBtn=new MyPushButtion(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        QLabel *label=new QLabel(menuBtn);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        connect(menuBtn,&MyPushButtion::clicked,[=](){
            QString str=QString("你选择的是第%1关").arg(i+1);
            qDebug()<<str;
            if(play==NULL)
            {
                chooseSound->play();
                this->hide();
                this->play =new PlayScene(i+1);
                play->setGeometry(this->geometry());
                this->play->show();
                connect(play,&PlayScene::back1,[=](){
                    this->setGeometry(play->geometry());
                    this->show();
                    delete play;
                    play=NULL;
                });
            }




        });
    }
}
