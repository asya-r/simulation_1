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
int period = 3;

QButtonGroup *btns = new QButtonGroup();

map<int, int> btn_sec = {
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 16; i++){
        btn_sec[i] = 0;
    }

    btns->addButton(ui->pushButton, 0);
    btns->addButton(ui->pushButton_2, 1);
    btns->addButton(ui->pushButton_3, 2);
    btns->addButton(ui->pushButton_4, 3);
    btns->addButton(ui->pushButton_5, 4);
    btns->addButton(ui->pushButton_6, 5);
    btns->addButton(ui->pushButton_7, 6);
    btns->addButton(ui->pushButton_8, 7);
    btns->addButton(ui->pushButton_9, 8);
    btns->addButton(ui->pushButton_10, 9);
    btns->addButton(ui->pushButton_11, 10);
    btns->addButton(ui->pushButton_12, 11);
    btns->addButton(ui->pushButton_13, 12);
    btns->addButton(ui->pushButton_14, 13);
    btns->addButton(ui->pushButton_15, 14);
    btns->addButton(ui->pushButton_16, 15);

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
        btn->setStyleSheet(WHITE);
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
    for (int i = 0; i < 16; i++){
        if (timer - btn_sec[i] > period){
            update_color(i);
        }
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    period = arg1;
}
