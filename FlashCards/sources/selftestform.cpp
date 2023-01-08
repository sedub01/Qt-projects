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
    this->mWordArray = wordArray;
    this->mRandomInputs = randomInputs;
    this->mDictArray = dictArray;
    reinit();
    inputAnswers();
}

void SelfTestForm::inputAnswers()
{
    ui->conditionLabel->setText(QString::number(mCurrentIndex) + ". " +
        mDictArray.at(mRandomInputs[mCurrentIndex - 1]).first + "\nПравильный перевод: \"" +
        mDictArray.at(mRandomInputs[mCurrentIndex - 1]).second + "\" \nВы перевели его как \"" +
            mWordArray[mCurrentIndex-1] + "\"\nПравильно ли оно переведено?");
}

void SelfTestForm::reinit()
{
    show();
    mCurrentIndex = 1;
    mYCount = mNCount = 0;
}

void SelfTestForm::answer(){
    const QPushButton *button = (QPushButton*)sender();

    (button->text() == "Да")? mYCount++ : mNCount++;
    mCurrentIndex++;
    if (mCurrentIndex - 1 == (int)mRandomInputs.size()){
        QMessageBox::critical(this, "Итого", "Ваш результат: " +
            QString::number(mYCount) + "/" + QString::number(mCurrentIndex - 1));
        hide();
        emit goToMainMenu();
    }
    else inputAnswers();
}
