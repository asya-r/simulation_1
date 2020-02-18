#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QButtonGroup"
#include "iostream"
#include "map"

using namespace std;


const QString WHITE = "background-color: rgb(238, 238, 236)";
const QString BLACK = "background-color: rgb(136, 138, 133)";
const QString GREEN = "background-color: rgb(156, 203, 71)";
const QString YELLOW = "background-color: rgb(232, 231, 93)";
const QString RED = "background-color: rgb(212, 83, 83)";
const QString BROWN = "background-color: rgb(143, 89, 2)";

int timer = 0;
const int PERIOD = 5;

QButtonGroup *btns = new QButtonGroup();

map<int, int> btn_sec = {
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QButtonGroup *btns = new QButtonGroup();
    btns->addButton(ui->pushButton, 0);
    btns->addButton(ui->pushButton_2, 1);
    btns->addButton(ui->pushButton_3, 2);
    btns->addButton(ui->pushButton_4, 3);

    connect(btns, SIGNAL(buttonClicked(int)), SLOT(buttonFromGroupClicked(int)));

    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonFromGroupClicked(int id){
    int money = ui->label->text().toInt();
    QAbstractButton *btn = btns->button(id);
    if (btn->styleSheet() == WHITE && money >= 2){
        btn->setStyleSheet(BLACK);
        ui->label->setText(QString::number(money-2));
    }
    else if (btn->styleSheet() == YELLOW){
        btn->setStyleSheet(WHITE);
        ui->label->setText(QString::number(money+3));
    }
    else if (btn->styleSheet() == RED){
        btn->setStyleSheet(WHITE);
        ui->label->setText(QString::number(money+5));
    }
    else if (btn->styleSheet() == BROWN && money >= 1){
        btn->setStyleSheet(BLACK);
        ui->label->setText(QString::number(money-1));
    }
}

void update_color(int id){
    QAbstractButton *btn = btns->button(id);
    if (btn->styleSheet() ==  BLACK){
        btn->setStyleSheet(GREEN);
        btn_sec[id] = timer;
    }
    else if (btn->styleSheet() ==  GREEN){
        btn->setStyleSheet(YELLOW);
        btn_sec[id] = timer;
    }
    else if (btn->styleSheet() ==  YELLOW){
        btn->setStyleSheet(RED);
        btn_sec[id] = timer;
    }
    else if (btn->styleSheet() ==  RED){
        btn->setStyleSheet(BROWN);
        btn_sec[id] = timer;
    }
}

void MainWindow::updateTime()
{

    timer++;
    ui->label_2->setText(QString::number(timer));
    for (int i = 0; i < 4; i++){
        if (timer - btn_sec[i] > PERIOD){
            update_color(i);
        }
    }
}
