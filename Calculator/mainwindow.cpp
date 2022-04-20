#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mathoperations.h"
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(deleteDigit()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(basicMathOperations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(basicMathOperations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(basicMathOperations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(basicMathOperations()));
    connect(ui->pushButton_switch, SIGNAL(clicked()), this, SLOT(switchTable()));
    connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(setConstants()));
    connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(setConstants()));
    connect(ui->pushButton_1divx, SIGNAL(clicked()), this, SLOT(shortOperations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(shortOperations()));
    connect(ui->pushButton_xfact, SIGNAL(clicked()), this, SLOT(shortOperations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(shortOperations()));


    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_div->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_switch->setCheckable(true);

    ui->pushButton_pow->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//добавляет текст на табло
void MainWindow::digitsNumbers()
{
    QPushButton *button = (QPushButton*)sender();


    button->setCheckable(true);
    button->setChecked(true);

    if (ui->pushButton_del->isChecked() && button->text() != "")
        ui->result_label->setText("");
    QString numbers;
    if (!ui->pushButton_div->isChecked())
        numbers = ui->result_label->text() + button->text();
    else numbers = button->text();
    //надо подправить!!!


    if (numbers.size() != 1 && numbers[0] == '0' && numbers[1] != '.')
        numbers.remove(0, 1);


    ui->result_label->setText(numbers);
    button->setChecked(false);
}


void MainWindow::on_pushButton_dot_clicked()
{
    QString temp = ui->result_label->text();
    if (!temp.contains("."))
        ui->result_label->setText(temp + ".");
}

void MainWindow::deleteDigit(){
    QString temp = ui->result_label->text();
    if (temp.size() > 1) temp.chop(1);
    else temp = "0";
    ui->result_label->setText(temp);
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton*)sender();
    double numbers = ui->result_label->text().toDouble();

    if (button->text() == "C"){
        numbers = 0;
        ui->pushButton_plus->setChecked(false);
        ui->pushButton_minus->setChecked(false);
        ui->pushButton_div->setChecked(false);
        ui->pushButton_mult->setChecked(false);
    }
    else if (button->text() == "%")
        numbers *= 0.01;
    ui->result_label->setText(QString::number(numbers));
}

void MainWindow::basicMathOperations(){
    QPushButton *button = (QPushButton*)sender();

    firstNum = ui->result_label->text().toDouble();
    //ui->result_label->setText("");
    //если нажать на цифру, потом на операцию, потом на другую операцию, то получится 0, так как
    //firstNum == "" (считай, предыдущее значение обнулилось)
    button->setChecked(true);

}

void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, secondNum = ui->result_label->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNumber = firstNum + secondNum;
        ui->result_label->setText(QString::number(labelNumber));
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked()){
        labelNumber = firstNum - secondNum;
        ui->result_label->setText(QString::number(labelNumber));
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_div->isChecked()){
        if (secondNum == 0) {
            QMessageBox::critical(this, "Ошибка", "Нельзя делить на 0!");
            labelNumber = firstNum;
        }
        else labelNumber = firstNum / secondNum;

        ui->result_label->setText(QString::number(labelNumber));
        ui->pushButton_div->setChecked(false);
    }
    else if(ui->pushButton_mult->isChecked()){
        labelNumber = firstNum * secondNum;
        ui->result_label->setText(QString::number(labelNumber));
        ui->pushButton_mult->setChecked(false);
    }
}

void MainWindow::switchTable(){

    if (ui->pushButton_switch->isChecked()){
        ui->pushButton_equal->setGeometry(240, 400, 61, 61);
        ui->pushButton_plus->setGeometry(240, 340, 61, 61);
        ui->pushButton_minus->setGeometry(240, 280, 61, 61);
        ui->pushButton_mult->setGeometry(240, 220, 61, 61);
        ui->pushButton_div->setGeometry(240, 160, 61, 61);

        ui->pushButton_dot->setGeometry(180, 400, 61, 61);
        ui->pushButton_3->setGeometry(180, 340, 61, 61);
        ui->pushButton_6->setGeometry(180, 280, 61, 61);
        ui->pushButton_9->setGeometry(180, 220, 61, 61);
        ui->pushButton_percent->setGeometry(180, 160, 61, 61);

        ui->pushButton_0->setGeometry(120, 400, 61, 61);
        ui->pushButton_2->setGeometry(120, 340, 61, 61);
        ui->pushButton_5->setGeometry(120, 280, 61, 61);
        ui->pushButton_8->setGeometry(120, 220, 61, 61);
        ui->pushButton_del->setGeometry(120, 160, 61, 61);

        ui->pushButton_e->setGeometry(60, 400, 61, 61);
        ui->pushButton_switch->setGeometry(0, 400, 61, 61);//особенная
        ui->pushButton_1->setGeometry(60, 340, 61, 61);
        ui->pushButton_4->setGeometry(60, 280, 61, 61);
        ui->pushButton_7->setGeometry(60, 220, 61, 61);
        ui->pushButton_clear->setGeometry(60, 160, 61, 61);

        ui->pushButton_pi->setGeometry(0, 340, 61, 61);
        ui->pushButton_1divx->setGeometry(0, 280, 61, 61);
        ui->pushButton_xfact->setGeometry(0, 220, 61, 61);
        ui->pushButton_sqrt->setGeometry(0, 160, 61, 61);
        ui->pushButton_pow->setGeometry(0, 100, 61, 61);
        ui->pushButton_second->setGeometry(0, 40, 61, 61);

        ui->pushButton_degrad->setGeometry(60, 40, 61, 61);
        ui->pushButton_sin->setGeometry(120, 40, 61, 61);
        ui->pushButton_cos->setGeometry(180, 40, 61, 61);
        ui->pushButton_tan->setGeometry(240, 40, 61, 61);
        ui->pushButton_lg->setGeometry(60, 100, 61, 61);
        ui->pushButton_ln->setGeometry(120, 100, 61, 61);
        ui->pushButton_leftBracket->setGeometry(180, 100, 61, 61);
        ui->pushButton_rightBracket->setGeometry(240, 100, 61, 61);

        ui->result_label->setGeometry(0, 0, 291, 41);
    }
    else {
        ui->pushButton_equal->setGeometry(225, 385, 76, 76);
        ui->pushButton_plus->setGeometry(225, 310, 76, 76);
        ui->pushButton_minus->setGeometry(225, 235, 76, 76);
        ui->pushButton_mult->setGeometry(225, 160, 76, 76);
        ui->pushButton_div->setGeometry(225, 85, 76, 76);

        ui->pushButton_dot->setGeometry(150, 385, 76, 76);
        ui->pushButton_3->setGeometry(150, 310, 76, 76);
        ui->pushButton_6->setGeometry(150, 235, 76, 76);
        ui->pushButton_9->setGeometry(150, 160, 76, 76);
        ui->pushButton_percent->setGeometry(150, 85, 76, 76);

        ui->pushButton_0->setGeometry(75, 385, 76, 76);
        ui->pushButton_2->setGeometry(75, 310, 76, 76);
        ui->pushButton_5->setGeometry(75, 235, 76, 76);
        ui->pushButton_8->setGeometry(75, 160, 76, 76);
        ui->pushButton_del->setGeometry(75, 85, 76, 76);

        ui->pushButton_e->setGeometry(300, 85, 1, 1);
        ui->pushButton_switch->setGeometry(0, 385, 76, 76);//особенная
        ui->pushButton_1->setGeometry(0, 310, 76, 76);
        ui->pushButton_4->setGeometry(0, 235, 76, 76);
        ui->pushButton_7->setGeometry(0, 160, 76, 76);
        ui->pushButton_clear->setGeometry(0, 85, 76, 76);

        ui->pushButton_pi->setGeometry(300, 85, 1, 1);
        ui->pushButton_1divx->setGeometry(300, 85, 1, 1);
        ui->pushButton_xfact->setGeometry(300, 85, 1, 1);
        ui->pushButton_sqrt->setGeometry(300, 85, 1, 1);
        ui->pushButton_pow->setGeometry(300, 85, 1, 1);
        ui->pushButton_second->setGeometry(300, 85, 1, 1);

        ui->pushButton_degrad->setGeometry(300, 85, 1, 1);
        ui->pushButton_sin->setGeometry(300, 85, 1, 1);
        ui->pushButton_cos->setGeometry(300, 85, 1, 1);
        ui->pushButton_tan->setGeometry(300, 85, 1, 1);
        ui->pushButton_lg->setGeometry(300, 85, 1, 1);
        ui->pushButton_ln->setGeometry(300, 85, 1, 1);
        ui->pushButton_leftBracket->setGeometry(300, 85, 1, 1);
        ui->pushButton_rightBracket->setGeometry(300, 85, 1, 1);

        ui->result_label->setGeometry(0, 0, 291, 81);
    }
    //button->setChecked(true); //без этой строчки работает!

}

void MainWindow::setConstants(){
    QPushButton *button = (QPushButton*)sender();
    if (button->text() == "π")
        ui->result_label->setText(QString::number(M_PI));
    else if (button->text() == "e")
        ui->result_label->setText(QString::number(M_E));
}

void MainWindow::shortOperations(){
    QPushButton *button = (QPushButton*)sender();
    double temp = ui->result_label->text().toDouble();
    if (button->text() == "1/x"){
        if (temp != 0)
            ui->result_label->setText(QString::number(1/temp));
        else QMessageBox::critical(this, "Ошибка", "Нельзя делить на 0!");
    }
    else if (button->objectName() == "pushButton_sqrt"){//на случай, если вместо текста картинка
        if (temp >= 0)
            ui->result_label->setText(QString::number(sqrt(temp)));
        else QMessageBox::critical(this, "Ошибка", "Нельзя извлекать корень из отрицательных чисел!");
    }
    else if (button->text() == "x!"){
        ui->result_label->setText(QString::number(factorial(temp)));
    }
    else if (ui->pushButton_pow->isChecked()){
        ui->result_label->setText(QString::number(pow(firstNum, temp)));

        ui->pushButton_pow->setChecked(false);
    }
}
