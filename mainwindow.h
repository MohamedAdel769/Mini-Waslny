#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Start_clicked();

    void on_exit_clicked();

private:
QMediaPlayer *strtmeow=new QMediaPlayer();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
