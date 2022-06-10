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
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(shortOperations()));
    connect(ui->pushButton_lg, SIGNAL(clicked()), this, SLOT(shortOperations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(basicMathOperations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometricFunctions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometricFunctions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometricFunctions()));
    connect(ui->pushButton_leftBracket, SIGNAL(clicked()), this, SLOT(putBrackets()));
    connect(ui->pushButton_rightBracket, SIGNAL(clicked()), this, SLOT(putBrackets()));


    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_div->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_switch->setCheckable(true);

    ui->pushButton_pow->setCheckable(true);
    ui->pushButton_second->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//добавляет текст на табло
void MainWindow::digitsNumbers()
{
    QPushButton *button = (QPushButton*)sender();
    QString numbers= ui->result_label->text() + button->text();
    //надо подправить!!!

    if (numbers.size() != 1 && numbers[0] == '0' && numbers[1] != '.')
        numbers.remove(0, 1);

    ui->result_label->setText(numbers);
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
    ui->result_label->setText("");
    //если нажать на цифру, потом на операцию, потом на другую операцию, то получится 0, так как
    //firstNum == "" (считай, предыдущее значение обнулилось)
    button->setChecked(true);

}

void MainWindow::on_pushButton_equal_clicked()
{
    QString text = ui->result_label->text();
    double labelNumber = 0, secondNum = text.toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNumber = firstNum + secondNum;
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked()){
        labelNumber = firstNum - secondNum;
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_div->isChecked()){
        if (secondNum == 0) {
            QMessageBox::critical(this, "Ошибка", "Нельзя делить на 0!");
            labelNumber = firstNum;
        }
        else labelNumber = firstNum / secondNum;
        ui->pushButton_div->setChecked(false);
    }
    else if(ui->pushButton_mult->isChecked()){
        labelNumber = firstNum * secondNum;
        ui->pushButton_mult->setChecked(false);
    }
    else if (ui->pushButton_pow->isChecked()){
        labelNumber = pow(firstNum, secondNum);
        ui->pushButton_pow->setChecked(false);
    }

    if (text.contains("arcsin")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        if(abs(secondNum) > 1) QMessageBox::critical(this, "Ошибка", "Значение должно находиться в диапазоне [-1; 1]!");
        else labelNumber = asin(secondNum) * 180 / M_PI;
    }
    else if (text.contains("arccos")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        if(abs(secondNum) > 1) QMessageBox::critical(this, "Ошибка", "Значение должно находиться в диапазоне [-1; 1]!");
        else labelNumber = acos(secondNum) * 180 / M_PI;
    }
    else if (text.contains("arctan")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        labelNumber = atan(secondNum) * 180 / M_PI;
    }
    else if (text.contains("sin")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        if (ui->pushButton_degrad->text() == "deg")
            labelNumber = sin(secondNum * M_PI / 180);
        else labelNumber = sin(secondNum);
    }
    else if (text.contains("cos")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        if (ui->pushButton_degrad->text() == "deg")
            labelNumber = cos(secondNum * M_PI / 180);
        else labelNumber = cos(secondNum);
    }
    else if (text.contains("tan")){
        secondNum = text.split("(").last().split(")").first().toDouble();
        if (ui->pushButton_degrad->text() == "deg")
            labelNumber = tan(secondNum * M_PI / 180);
        else labelNumber = tan(secondNum);
    }
    if (abs(labelNumber) < eps) labelNumber = 0;

    ui->result_label->setText(QString::number(labelNumber, 'g', 10));
    if (labelNumber > inf) ui->result_label->setText("∞");
}

void MainWindow::switchTable(){

    if (ui->pushButton_switch->isChecked()){
        ui->pushButton_equal->setGeometry(240, 395, 61, 61);
        ui->pushButton_plus->setGeometry(240, 335, 61, 61);
        ui->pushButton_minus->setGeometry(240, 275, 61, 61);
        ui->pushButton_mult->setGeometry(240, 215, 61, 61);
        ui->pushButton_div->setGeometry(240, 155, 61, 61);

        ui->pushButton_dot->setGeometry(180, 395, 61, 61);
        ui->pushButton_3->setGeometry(180, 335, 61, 61);
        ui->pushButton_6->setGeometry(180, 275, 61, 61);
        ui->pushButton_9->setGeometry(180, 215, 61, 61);
        ui->pushButton_percent->setGeometry(180, 155, 61, 61);

        ui->pushButton_0->setGeometry(120, 395, 61, 61);
        ui->pushButton_2->setGeometry(120, 335, 61, 61);
        ui->pushButton_5->setGeometry(120, 275, 61, 61);
        ui->pushButton_8->setGeometry(120, 215, 61, 61);
        ui->pushButton_del->setGeometry(120, 155, 61, 61);

        ui->pushButton_e->setGeometry(60, 395, 61, 61);
        ui->pushButton_switch->setGeometry(0, 395, 61, 61);//особенная
        ui->pushButton_1->setGeometry(60, 335, 61, 61);
        ui->pushButton_4->setGeometry(60, 275, 61, 61);
        ui->pushButton_7->setGeometry(60, 215, 61, 61);
        ui->pushButton_clear->setGeometry(60, 155, 61, 61);

        ui->pushButton_pi->setGeometry(0, 335, 61, 61);
        ui->pushButton_1divx->setGeometry(0, 275, 61, 61);
        ui->pushButton_xfact->setGeometry(0, 215, 61, 61);
        ui->pushButton_sqrt->setGeometry(0, 155, 61, 61);
        ui->pushButton_pow->setGeometry(0, 95, 61, 61);
        ui->pushButton_second->setGeometry(0, 35, 61, 61);

        ui->pushButton_degrad->setGeometry(60, 35, 61, 61);
        ui->pushButton_sin->setGeometry(120, 35, 61, 61);
        ui->pushButton_cos->setGeometry(180, 35, 61, 61);
        ui->pushButton_tan->setGeometry(240, 35, 61, 61);
        ui->pushButton_lg->setGeometry(60, 95, 61, 61);
        ui->pushButton_ln->setGeometry(120, 95, 61, 61);
        ui->pushButton_leftBracket->setGeometry(180, 95, 61, 61);
        ui->pushButton_rightBracket->setGeometry(240, 95, 61, 61);

        ui->result_label->setGeometry(0, 0, 291, 36);
    }
    else {
        ui->pushButton_equal->setGeometry(225, 380, 76, 76);
        ui->pushButton_plus->setGeometry(225, 305, 76, 76);
        ui->pushButton_minus->setGeometry(225, 230, 76, 76);
        ui->pushButton_mult->setGeometry(225, 155, 76, 76);
        ui->pushButton_div->setGeometry(225, 80, 76, 76);

        ui->pushButton_dot->setGeometry(150, 380, 76, 76);
        ui->pushButton_3->setGeometry(150, 305, 76, 76);
        ui->pushButton_6->setGeometry(150, 230, 76, 76);
        ui->pushButton_9->setGeometry(150, 155, 76, 76);
        ui->pushButton_percent->setGeometry(150, 80, 76, 76);

        ui->pushButton_0->setGeometry(75, 380, 76, 76);
        ui->pushButton_2->setGeometry(75, 305, 76, 76);
        ui->pushButton_5->setGeometry(75, 230, 76, 76);
        ui->pushButton_8->setGeometry(75, 155, 76, 76);
        ui->pushButton_del->setGeometry(75, 80, 76, 76);

        ui->pushButton_e->setGeometry(300, 80, 1, 1);
        ui->pushButton_switch->setGeometry(0, 380, 76, 76);//особенная
        ui->pushButton_1->setGeometry(0, 305, 76, 76);
        ui->pushButton_4->setGeometry(0, 230, 76, 76);
        ui->pushButton_7->setGeometry(0, 155, 76, 76);
        ui->pushButton_clear->setGeometry(0, 80, 76, 76);

        ui->pushButton_pi->setGeometry(300, 80, 1, 1);
        ui->pushButton_1divx->setGeometry(300, 80, 1, 1);
        ui->pushButton_xfact->setGeometry(300, 80, 1, 1);
        ui->pushButton_sqrt->setGeometry(300, 80, 1, 1);
        ui->pushButton_pow->setGeometry(300, 80, 1, 1);
        ui->pushButton_second->setGeometry(300, 80, 1, 1);

        ui->pushButton_degrad->setGeometry(300, 80, 1, 1);
        ui->pushButton_sin->setGeometry(300, 80, 1, 1);
        ui->pushButton_cos->setGeometry(300, 80, 1, 1);
        ui->pushButton_tan->setGeometry(300, 80, 1, 1);
        ui->pushButton_lg->setGeometry(300, 80, 1, 1);
        ui->pushButton_ln->setGeometry(300, 80, 1, 1);
        ui->pushButton_leftBracket->setGeometry(300, 80, 1, 1);
        ui->pushButton_rightBracket->setGeometry(300, 80, 1, 1);

        ui->result_label->setGeometry(0, 0, 291, 81);
    }
    //button->setChecked(true); //без этой строчки работает!

}

void MainWindow::setConstants(){
    QPushButton *button = (QPushButton*)sender();
    if (button->text() == "π")
        ui->result_label->setText(QString::number(M_PI, 'g', 10));
    else if (button->text() == "e")
        ui->result_label->setText(QString::number(M_E, 'g', 10));
}

void MainWindow::shortOperations(){
    QPushButton *button = (QPushButton*)sender();
    double temp = ui->result_label->text().toDouble();
    if (button->text() == "1/x"){
        if (temp != 0)
            ui->result_label->setText(QString::number(1/temp, 'g', 10));
        else QMessageBox::critical(this, "Ошибка", "Нельзя делить на 0!");
    }
    else if (button->objectName() == "pushButton_sqrt"){//на случай, если вместо текста картинка
        if (temp >= 0)
            ui->result_label->setText(QString::number(sqrt(temp), 'g', 10));
        else QMessageBox::critical(this, "Ошибка", "Нельзя извлекать корень из отрицательных чисел!");
    }
    else if (button->text() == "x!"){
        ui->result_label->setText(QString::number(factorial(temp)));
    }
    else if (button->text() == "ln"){
        ui->result_label->setText(QString::number(log(temp), 'g', 10));
    }
    else if (button->text() == "lg"){
        ui->result_label->setText(QString::number(log10(temp), 'g', 10));
    }
}

void MainWindow::on_pushButton_second_clicked(){
    if (ui->pushButton_second->isChecked()){
        ui->pushButton_sin->setText("sin⁻¹");
        ui->pushButton_cos->setText("cos⁻¹");
        ui->pushButton_tan->setText("tan⁻¹");
        ui->pushButton_degrad->setEnabled(false);
    }
    else{
        ui->pushButton_sin->setText("sin");
        ui->pushButton_cos->setText("cos");
        ui->pushButton_tan->setText("tan");
        ui->pushButton_degrad->setEnabled(true);
    }
}

void MainWindow::on_pushButton_degrad_clicked()
{
    if (ui->pushButton_degrad->text() == "deg"){
        ui->pushButton_second->setEnabled(false);
        ui->pushButton_degrad->setText("rad");
    }
    else {
        ui->pushButton_second->setEnabled(true);
        ui->pushButton_degrad->setText("deg");
    }
}

//надо потом сделать так, чтобы калькулятор обрабатывал тригонометрические ф-ии
//и адаптировать под это остальные операции (del, = и тд)
void MainWindow::trigonometricFunctions(){
    QPushButton *button = (QPushButton*)sender();
    QString numbers = ui->result_label->text();
    if (numbers == "0") numbers = "";
    if (button->text() == "sin")
        ui->result_label->setText(numbers + "sin(");
    else if (button->text() == "sin⁻¹")
        ui->result_label->setText(numbers + "arcsin(");
    else if (button->text() == "cos")
        ui->result_label->setText(numbers + "cos(");
    else if (button->text() == "cos⁻¹")
        ui->result_label->setText(numbers + "arccos(");
    else if (button->text() == "tan")
        ui->result_label->setText(numbers + "tan(");
    else if (button->text() == "tan⁻¹")
        ui->result_label->setText(numbers + "arctan(");
}

void MainWindow::putBrackets(){
    QPushButton *button = (QPushButton*)sender();
    QString temp = ui->result_label->text();

    ui->result_label->setText(temp + button->text());
}
