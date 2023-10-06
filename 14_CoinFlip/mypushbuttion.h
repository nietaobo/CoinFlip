#ifndef MYPUSHBUTTION_H
#define MYPUSHBUTTION_H
#include<QPushButton>
#include <QWidget>

class MyPushButtion : public QPushButton
{
    Q_OBJECT
public:
    MyPushButtion(QString normalImg,QString pressing="");
    QString normalImgPath;
    QString pressingPath;

    void zoom();

signals:

};

#endif // MYPUSHBUTTION_H
