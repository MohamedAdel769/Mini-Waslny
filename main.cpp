#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainWindow *window = new MainWindow;
    window->show();

    return prog.exec();
}
