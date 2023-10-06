#include "playscene.h"
#include<QPainter>
#include <QPixmap>
#include<QWidget>
#include<mypushbuttion.h>
#include<QMenuBar>
#include<QDebug>
#include<QLabel>
#include<mycoin.h>
#include<dataconfig.h>
#include<QTimer>
#include<QPropertyAnimation>
#include <QEasingCurve>
#include<QSound>

PlayScene::PlayScene(int num)
{
    //背景
    this->number=num;
    this->setFixedSize(320,580);
    QString str=QString("翻金币第%1关").arg(num);
    this->setWindowTitle(str);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //菜单栏
    QMenuBar *bar=new QMenuBar(this);
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitMenu=startMenu->addAction("退出");
    connect(quitMenu,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    this->back();

    //显示关卡
    this->showLevel();

    //初始化二维数组
    dataConfig fig;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=fig.mData[this->number][i][j];
        }

    }

    //显示金币,一定要放到初始化后面，我的天
    this->showCoin();

    //胜利图片
    this->showPic();
}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width()*0.5,pix.height()*0.5,pix);

}

void PlayScene::back()
{
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    MyPushButtion *backBtn=new MyPushButtion(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButtion::clicked,[=](){
        qDebug()<<"你想要返回吗";
        backSound->play();
        this->hide();
        emit this->back1();

    });
}

//显示关卡
void PlayScene::showLevel()
{
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("level %1").arg(this->number);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-70,140,50));

}

//显示金币
void PlayScene::showCoin()
{
    QSound *flipSound=new QSound(":/res/ConFlipSound.wav",this);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(label);
            coin->move(label->width()*0.08,label->height()*0.08);
            coinBtn[i][j]=coin;
            coin->posx=i;
            coin->posy=j;
            //coin->flag=this->gameArray[i][j]==1?true:false;
            coin->flag=gameArray[i][j];

            connect(coin,&MyCoin::clicked,[=](){
                qDebug()<<"点击了"<<coin->posx<<"和"<<coin->posy;
                qDebug()<<coin->flag;
                flipSound->play();
                coin->changeFlag();
                gameArray[i][j]=gameArray[i][j]==0?1:0;
                this->flipCoin(coin);
            });
        }

    }
}

//翻动周围金币
void PlayScene::flipCoin(MyCoin *coin)
{
    QSound *winSound =new QSound(":/res/LevelWinSound.wav");
    QTimer::singleShot(300,this,[=](){
        if(coin->posx+1<4)
           {
               this->coinBtn[coin->posx+1][coin->posy]->changeFlag();
               gameArray[coin->posx+1][coin->posy]=gameArray[coin->posx+1][coin->posy]==0?1:0;
           }
           if(coin->posx-1>=0)
           {
               this->coinBtn[coin->posx-1][coin->posy]->changeFlag();
               gameArray[coin->posx-1][coin->posy]=gameArray[coin->posx-1][coin->posy]==0?1:0;
           }
           if(coin->posy+1<4)
           {
               this->coinBtn[coin->posx][coin->posy+1]->changeFlag();
               gameArray[coin->posx][coin->posy+1]=gameArray[coin->posx][coin->posy+1]==0?1:0;
           }
           if(coin->posy-1>=0)
           {
               this->coinBtn[coin->posx][coin->posy-1]->changeFlag();
               gameArray[coin->posx][coin->posy-1]=gameArray[coin->posx][coin->posy-1]==0?1:0;
           }
           this->allNum=0;
           for(int i=0;i<4;i++)
           {
               for(int j=0;j<4;j++)
               {
                   this->allNum+=gameArray[i][j];
               }
           }
           if(this->allNum==16)
           {
               qDebug()<<"你胜利了";
               winSound->play();
               this->turnPic();
               for(int i=0;i<4;i++)
               {
                   for(int j=0;j<4;j++)
                   {
                       this->coinBtn[i][j]->isWin=true;
                   }
               }
           }
    });
}


//胜利图片
void PlayScene::showPic()
{
    //QLabel *winlabel=new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    this->winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->setPixmap(pix);
    winlabel->setParent(this);
    winlabel->move((this->width()-pix.width())*0.5, -pix.height());
}

//图片翻过来
void PlayScene::turnPic()
{
    QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


