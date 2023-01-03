#include <QMessageBox>
#include "headers/selftestform.h"
#include "headers/mainwindow.h"
#include "ui_selftestform.h"

SelfTestForm::SelfTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestForm)
{
    ui->setupUi(this);
    for (const auto& button: {ui->yesButton, ui->noButton}){
        connect(button, &QPushButton::clicked,
                this, &SelfTestForm::answer);
    }
}

SelfTestForm::~SelfTestForm()
{
    delete ui; //больше ничего не удаляется, т.к. объект хранит в себе только указатели
}

void SelfTestForm::gotoSelfTestForm(vector<QString>& wordArray, vector<int>& randomInputs,
                                    QVector<std::pair<QString, QString> > &dictArray){
    this->wordArray = wordArray;
    this->randomInputs = randomInputs;
    this->dictArray = dictArray;
    reinit();
    inputAnswers();
}

void SelfTestForm::inputAnswers()
{
    ui->conditionLabel->setText(QString::number(index) + ". " +
        dictArray.at(randomInputs[index - 1]).first + "\nПравильный перевод: \"" +
        dictArray.at(randomInputs[index - 1]).second + "\" \nВы перевели его как \"" +
            wordArray[index-1] + "\"\nПравильно ли оно переведено?");
}

void SelfTestForm::reinit()
{
    show();
    index = 1;
    yesCount = noCount = 0;
}

void SelfTestForm::answer(){
    QPushButton *button = (QPushButton*)sender();

    (button->text() == "Да")? yesCount++ : noCount++;
    index++;
    if (index - 1 == (int)randomInputs.size()){
        QMessageBox::critical(this, "Итого", "Ваш результат: " + QString::number(yesCount) + "/" + QString::number(index - 1));
        hide();
        emit goToMainMenu();
    }
    else inputAnswers();
}
