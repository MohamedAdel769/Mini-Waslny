#include "mainwindow.h"
#include "citywindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap bg(":/images/rsz_1bg.png");
    QPalette palet;
    palet.setBrush(QPalette::Background, bg);
    this->setPalette(palet);
    ui->setupUi(this);
    QPixmap logo(":/images/logo2.png");
    ui->label->setPixmap(logo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_clicked()
{
    CityWindow *main = new CityWindow;
    main->show();
    this->hide();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}
