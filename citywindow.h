#ifndef CITYWINDOW_H
#define CITYWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "mainwindow.h"

namespace Ui {
class CityWindow;
}

class CityWindow : public QMainWindow
{
    Q_OBJECT
QMediaPlayer *meow=new QMediaPlayer();

public:
    explicit CityWindow(QWidget *parent = nullptr);
    ~CityWindow();

private slots:
    void on_main_menu_clicked();

    void on_updBtn_clicked();

    void on_deleteBtn_clicked();

    void on_SPBtn_clicked();

    void on_dispBtn_clicked();

    void on_addDistBtn_clicked();

    void on_addTownBtn_clicked();

    void on_Add_dist_clicked();

    void on_getSP_btn_clicked();

    void on_upd_options_currentIndexChanged(int index);

    void upd_options_enabled(bool);

    void on_upd_btn_clicked();

    void on_pushButton_clicked();

public:
    Ui::CityWindow *ui;
    Graph city ;
};

#endif // CITYWINDOW_H
