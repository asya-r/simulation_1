#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QButtonGroup"


const QString WHITE = "background-color: rgb(238, 238, 236)";
const QString BLACK = "background-color: rgb(136, 138, 133)";
const QString GREEN = "background-color: rgb(156, 203, 71)";
const QString YELLOW = "background-color: rgb(232, 231, 93)";
const QString RED = "background-color: rgb(212, 83, 83)";
const QString BROWN = "background-color: rgb(143, 89, 2)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup *btns = new QButtonGroup();
    btns->addButton(ui->pushButton, 0);
    btns->addButton(ui->pushButton_2, 1);
    btns->addButton(ui->pushButton_3, 2);
    btns->addButton(ui->pushButton_4, 3);

    connect(btns, SIGNAL(buttonClicked(QAbstractButton *)), SLOT(buttonFromGroupClicked(QAbstractButton *)));

    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonFromGroupClicked(QAbstractButton *btn){
    int money = ui->label->text().toInt();
    if (btn->styleSheet() == WHITE && money >= 2){
        btn->setStyleSheet(BLACK);
        ui->label->setText(QString::number(money-2));
    }
}

void updateColor(){

}

void MainWindow::updateTime()
{
    ui->label_2->setText(QTime::currentTime().toString());
    updateColor();
}
