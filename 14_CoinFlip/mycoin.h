#ifndef MYCOIN_H
#define MYCOIN_H
#include<QPushButton>
#include <QWidget>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);

    //翻金币
    void changeFlag();

    //翻转
    void coinFlag();

    //重写鼠标事件
    void mousePressEvent(QMouseEvent *event);

public:
    int posx;  //x坐标
    int posy;   //y坐标
    bool flag;   //正反标志

    QTimer *timer=NULL; //定时器

    int min=1;
    int max=8;

    bool isAnimaion=false;

    bool isWin=false;   //胜利标志

signals:

};

#endif // MYCOIN_H
