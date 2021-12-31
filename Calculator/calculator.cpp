#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++){
        QString butName = "Button"+QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->ButtonA, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonS, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonM, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonD, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->ButtonE, SIGNAL(released()), this,
            SLOT(EqualButton()));

    connect(ui->ButtonC, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayval = ui->Display->text();
    if((displayval.toDouble()==0)||(displayval.toDouble()==0.0)){
        ui->Display->setText(butval);
    }else{
        QString newVal=displayval + butval;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/",Qt::CaseInsensitive)==0){
        divTrigger=true;
    }else if(QString::compare(butVal, "*",Qt::CaseInsensitive)==0){
        mulTrigger=true;
    }else if(QString::compare(butVal, "-",Qt::CaseInsensitive)==0){
        subTrigger=true;
    }else if(QString::compare(butVal, "+",Qt::CaseInsensitive)==0){
        addTrigger=true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(mulTrigger){
            solution = calcVal * dblDisplayVal;
        }else{
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    /*QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText((QString::number(dblDisplayValSign)));
    }*/
    ui->Display->setText("0.0");
}




















