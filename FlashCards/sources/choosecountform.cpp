#include "headers/choosecountform.h"
#include "ui_choosecountform.h"

ChoosecountForm::ChoosecountForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoosecountForm)
{
    ui->setupUi(this);
}

ChoosecountForm::~ChoosecountForm()
{
    delete ui;
    delete answerform;
    answerform = nullptr;
}

void ChoosecountForm::addForm(AnswerForm* answerform){
    this->answerform = answerform;
    connect(this, &ChoosecountForm::signal, this->answerform, &AnswerForm::slot);
    //теперь сигнал и слот соединены друг с другом
}

void ChoosecountForm::on_pushButton_clicked()
{
    hide();
    answerform->show();
    emit signal(ui->comboBox->currentText()); //вызов сигнала и передача кол-ва слов
}

