#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <QPaintEvent>
#include <QMainWindow>
#include<QLabel>
#include<mycoin.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int num);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //返回按钮
    void back();

    //显示关卡
    void showLevel();

    //显示金币
    void showCoin();

    //翻动周围金币
    void flipCoin(MyCoin *coin);

    //胜利图片
    void showPic();

    //图片翻过来
    void turnPic();

public:
    int number;

    int gameArray[4][4];

    MyCoin *coinBtn[4][4]; //记录按钮

    int allNum=0;

    QLabel *winlabel=new QLabel;

signals:
    void back1();

};

#endif // PLAYSCENE_H
