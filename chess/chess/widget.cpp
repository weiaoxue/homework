#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_play_clicked()
{
    this->hide();
    dlg = new Dialog(15, this);
    dlg->show();
    dlg->exec();
    this->show();
}

void Widget::on_go_clicked()
{
    this->hide();
    dlg = new Dialog(19, this);
    dlg->show();
    dlg->exec();
    this->show();
}

void Widget::on_quit_clicked()
{
    this->close();
}
