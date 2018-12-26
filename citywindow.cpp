#include "citywindow.h"
#include "ui_citywindow.h"
#include <QString>
#include <string>
#include <QStringList>
#include <QMessageBox>
#include <iostream>

using namespace std;

CityWindow::CityWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CityWindow)
{
    ui->setupUi(this);
    city.initialize();
    ui->stackedWidget->setCurrentIndex(0);
    QStringList initial_towns = {"A", "E", "B", "C", "F", "D"};
    ui->towns_list->addItems(initial_towns);
    ui->towns_list2->addItems(initial_towns);
    ui->towns_list_2->addItems(initial_towns);
    ui->towns_list2_2->addItems(initial_towns);
    ui->towns_list_3->addItems(initial_towns);
    ui->towns_list2_3->addItems(initial_towns);
}

CityWindow::~CityWindow()
{
    delete ui;
}

void CityWindow::on_main_menu_clicked()
{
    ui->input_txt->setEnabled(false);
    MainWindow *temp = new MainWindow;
    temp->show();
    this->close();
}

void CityWindow::on_updBtn_clicked()
{
    ui->input_txt->setEnabled(false);
    ui->inst_label->setText("Choose an update option then enter the data you want to update it, click update!");
    upd_options_enabled(false);
    ui->upd_options->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(3);
}

void CityWindow::on_deleteBtn_clicked()
{
    meow->setMedia(QUrl("qrc:/images/oh-boy.mp3"));
    meow->play();
    ui->stackedWidget->setCurrentIndex(0);
    ui->input_txt->setEnabled(false);
    ui->output_txt->clear();
    ui->input_txt->clear();
    if(!city.isEmpty()){
        city.user = true ;
        city.delete_graph();
        ui->output_txt->setText("City deleted Successfully!");
        ui->towns_list->clear();
        ui->towns_list2->clear();
        ui->towns_list_2->clear();
        ui->towns_list_3->clear();
        ui->towns_list2_2->clear();
        ui->towns_list2_3->clear();
    }
    else{
        ui->output_txt->setText("City is already Empty!");
    }
}

void CityWindow::on_SPBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->SP_output->clear();
    ui->input_txt->setEnabled(false);
}

void CityWindow::on_dispBtn_clicked()
{
    ui->input_txt->setEnabled(false);
    ui->output_txt->clear();
    ui->stackedWidget->setCurrentIndex(0);
    QString temp = city.display_graph();
    ui->output_txt->setText(temp);
}

void CityWindow::on_addDistBtn_clicked()
{
    ui->input_txt->setEnabled(false);
    ui->dist_val->text().clear();
    ui->instructions_txt->setText("Choose the towns then enter the distance between them, then click Add!");
    ui->stackedWidget->setCurrentIndex(1);
}

void CityWindow::on_addTownBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->input_txt->setEnabled(true);
    ui->output_txt->clear();
    ui->input_txt->setFocus();
    QString town = ui->input_txt->toPlainText();
    if(town == "")
        ui->output_txt->setText("Please enter the town name to add it.");
    else{
        city.user = true ;
        town = city.add_town(town);
        if(town=="Town already exist")
        {
             ui->output_txt->setText(town);
        }
        else
        {
            ui->towns_list->addItem(town);
            ui->towns_list2->addItem(town);
            ui->towns_list_2->addItem(town);
            ui->towns_list_3->addItem(town);
            ui->towns_list2_2->addItem(town);
            ui->towns_list2_3->addItem(town);
            ui->output_txt->setText(town + " added to the city successfully!");
        }

    }
    ui->input_txt->clear();
}

void CityWindow::on_Add_dist_clicked()
{
    QString A = ui->towns_list->currentText();
    QString B = ui->towns_list2->currentText();
    if (A==B)
    {
        ui->instructions_txt->setText("Can't add distance between the same town!");
    }
    else
    {
        long long dist = ui->dist_val->text().toLong();
        bool validation = city.isvalid("Add", A, B) ;
        if(dist > 0){
            if(validation){
                city.user = true ;
                city.add_distance(A, B, dist);
                ui->instructions_txt->setText("Distance added Successfully!");
            }
            else{
                 ui->instructions_txt->setText("There is already distance between the selected towns.");
            }
        }
        else if(dist == 0){
            ui->instructions_txt->setText("Distance can't be zero/empty.");
        }
        else{
            ui->instructions_txt->setText("Distance can't be negative.");
        }
    }
    ui->dist_val->clear();
}

void CityWindow::upd_options_enabled(bool flag){
    ui->town_label->setEnabled(flag);
    ui->town2_label->setEnabled(flag);
    ui->dist_label->setEnabled(flag);
    ui->towns_list_3->setEnabled(flag);
    ui->towns_list2_3->setEnabled(flag);
    ui->dist_val_2->setEnabled(flag);
    ui->upd_btn->setEnabled(flag);
}

void CityWindow::on_getSP_btn_clicked()
{
    QString A = ui->towns_list_2->currentText();
    QString B = ui->towns_list2_2->currentText();
    city.apply_dijkstra();
    city.apply_floyd();
    bool Validation = city.isvalid("SP", A, B) ;
    if(Validation){
        QString output = city.get_shortestPath(A, B);
        ui->SP_output->setText(output);
    }
    else
        ui->SP_output->setText("No Path Found!");
}

void CityWindow::on_upd_options_currentIndexChanged(int index)
{
    upd_options_enabled(false);
    ui->dist_val_2->clear();
    if(index == 1){ // delete town
        ui->town_label->setText("Town");
        ui->town_label->setEnabled(true);
        ui->towns_list_3->setEnabled(true);
        ui->upd_btn->setEnabled(true);
    }
    else if(index == 2){ // edit dist
        ui->town_label->setText("First Town");
        upd_options_enabled(true);
    }
    else if(index == 3){ // delete dist
        ui->town_label->setText("First Town");
        ui->town_label->setEnabled(true);
        ui->town2_label->setEnabled(true);
        ui->towns_list_3->setEnabled(true);
        ui->towns_list2_3->setEnabled(true);
        ui->upd_btn->setEnabled(true);
    }
}

void CityWindow::on_upd_btn_clicked()
{
    int index = ui->upd_options->currentIndex();
    city.user = true ;
    if(index == 1){
        bool tmp;
        int index = ui->towns_list_3->currentIndex();
        QString del_town = ui->towns_list_3->currentText();
        city.del_town(del_town);
        ui->inst_label->setText(del_town + " deleted Successfully!");
        ui->towns_list->removeItem(index);
        ui->towns_list2->removeItem(index);
        ui->towns_list_2->removeItem(index);
        ui->towns_list_3->removeItem(index);
        ui->towns_list2_2->removeItem(index);
        ui->towns_list2_3->removeItem(index);
    }
    else if(index == 2){
        QString A = ui->towns_list_3->currentText();
        QString B = ui->towns_list2_3->currentText();
        long long newDist = ui->dist_val_2->text().toLong();
        if(newDist > 0){
            bool validation = city.isvalid("upd", A, B) ;
            if(validation){
                city.edit_dist(A, B, newDist);
                ui->inst_label->setText("New Distance added Successfully!");
            }
            else
                ui->inst_label->setText("There is no distance between the chosen towns.");
        }
        else if(newDist == 0){
            ui->inst_label->setText("Distance can't be zero/empty.");
        }
        else{
            ui->inst_label->setText("Distance can't be negative.");
        }
    }
    else{
        QString A = ui->towns_list_3->currentText();
        QString B = ui->towns_list2_3->currentText();
        bool validation = city.isvalid("upd", A, B) ;
        if(validation){
            ui->inst_label->setText("Distance deleted Successfully!");
            city.remove_edge(A, B);
        }
        else
            ui->inst_label->setText("There is no distance between the chosen towns.");
    }
}

void CityWindow::on_pushButton_clicked()
{
    city.Undo();
    ui->towns_list->clear();
    ui->towns_list2->clear();
    ui->towns_list_2->clear();
    ui->towns_list_3->clear();
    ui->towns_list2_2->clear();
    ui->towns_list2_3->clear();
    city.Fill(ui->towns_list);
    city.Fill(ui->towns_list2);
    city.Fill(ui->towns_list_2);
    city.Fill(ui->towns_list_3);
    city.Fill(ui->towns_list2_2);
    city.Fill(ui->towns_list2_3);
    on_dispBtn_clicked();
}
