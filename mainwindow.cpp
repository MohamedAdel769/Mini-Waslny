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
    strtmeow->setMedia(QUrl("qrc:/images/Bongo_Cat_-_BLACKPINK_DDU-DU_DDU-DU_K-POP[Converterino.online].mp3"));
    strtmeow->play();
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
    strtmeow->stop();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}
