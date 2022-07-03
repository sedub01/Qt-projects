#include <QMessageBox>
#include "headers/selftestform.h"
#include "ui_selftestform.h"

SelfTestForm::SelfTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestForm)
{
    ui->setupUi(this);
    connect(ui->yesButton, SIGNAL(clicked()), this, SLOT(answer()));
    connect(ui->noButton, SIGNAL(clicked()), this, SLOT(answer()));
}

SelfTestForm::~SelfTestForm()
{
    delete ui; //больше ничего не удаляется, т.к. объект хранит в себе только указатели
}

void SelfTestForm::slot(vector<QString>& wordArray, vector<int>& randomInputs, QString **dictArray){
    this->wordArray = wordArray;
    this->randomInputs = randomInputs;
    this->dictArray = dictArray;

    inputAnswers();
}

void SelfTestForm::inputAnswers()
{
    ui->conditionLabel->setText(QString::number(index) + ". " + dictArray[randomInputs[index - 1]][0] + "\nПравильный перевод: \"" +
            dictArray[randomInputs[index - 1]][1] + "\" \nВы перевели его как \"" + wordArray[index-1] +
            "\"\nПравильно ли оно переведено?");
}

void SelfTestForm::answer(){
    QPushButton *button = (QPushButton*)sender();

    (button->text() == "Да")? yesCount++ : noCount++;
    index++;
    if (index - 1 == (int)randomInputs.size()){
        QMessageBox::critical(this, "Итого", "Ваш результат: " + QString::number(yesCount) + "/" + QString::number(index - 1));
        exit(0);//хочу осуществить переход на главное окно
    }
    else inputAnswers();
}
