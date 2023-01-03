#include "headers/choosecountform.h"
#include "ui_choosecountform.h"

ChoosecountForm::ChoosecountForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoosecountForm)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &ChoosecountForm::goToAnswerForm);
}

ChoosecountForm::~ChoosecountForm()
{
    delete ui;
}

void ChoosecountForm::goToAnswerForm()
{
    hide();
    emit nWordsChosen(ui->comboBox->currentText().toInt());
}

