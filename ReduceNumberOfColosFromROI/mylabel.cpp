#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit Mouse_Pos();
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void MyLabel::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}

