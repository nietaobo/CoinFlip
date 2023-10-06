#ifndef CHOOSELEVELSCENCE_H
#define CHOOSELEVELSCENCE_H
#include"playscene.h"
#include <QMainWindow>
#include<QSound>

class ChooseLevelScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScence(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    void menuScence();

    PlayScene *play=NULL;

    QSound *chooseSound=NULL;

signals:
    void choose();
};

#endif // CHOOSELEVELSCENCE_H
