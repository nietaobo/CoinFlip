#include "mainscene.h"
#include "ui_mainscene.h"
#include <QAction>
#include <QPaintEvent>
#include <QPixmap>
#include<QPainter>
#include<mypushbuttion.h>
#include<QDebug>
#include<chooselevelscence.h>
#include<QTimer>
#include<QSound>


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //5、开始音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav",this);

    //1、主要窗口
    setFixedSize(320,580);
    setWindowTitle("涛波翻金币");
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });


    //2、弹起来的按钮
    MyPushButtion *startButton=new MyPushButtion(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move((this->width()*0.5-startButton->width()*0.5),this->height()*0.7);


    //3、特效开始弹起来的按钮
    ChooseLevelScence *chooseScence=new ChooseLevelScence(this);
    connect(startButton,&MyPushButtion::clicked,[=](){       
            qDebug()<<"点击了按钮";
            startButton->zoom();
            startSound->play();
            QTimer::singleShot(500,this,[=](){
            //this->setGeometry(chooseScence->geometry());
            chooseScence->setGeometry(this->geometry());
            this->hide();
            chooseScence->show();
        });

    });


    //4、返回按钮功能实现
    connect(chooseScence,&ChooseLevelScence::choose,[=](){
        this->setGeometry(chooseScence->geometry());
        chooseScence->hide();
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}
void MainScene::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/11.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);

   pix.load(":/res/Title.png");
   pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
   painter.drawPixmap(10,30,pix);
}
