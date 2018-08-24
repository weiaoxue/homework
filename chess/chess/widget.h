#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_play_clicked();

    void on_go_clicked();

    void on_quit_clicked();

private:
    Ui::Widget *ui;
    Dialog *dlg;
};

#endif // WIDGET_H
