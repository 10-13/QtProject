#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::shared_ptr<DValue> MainWindow::GetResult() {
    auto res = std::make_shared<DValue>("Event");
    res->Add("Mood")->Add(ui->eventbox->currentText().toStdString());
    res->Add("Weather")->Add(ui->weatherbox->currentText().toStdString());
    res->Add("Temperature")->Add(QString::number(ui->temperaturebox->value()).toStdString());
    res->Add("Officiality")->Add(ui->officialbox->currentText().toStdString());
    return res;
}
