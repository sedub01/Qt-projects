#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/mainIcon.png");
    int w = ui->mainImage->width(), h = ui->mainImage->height();
    ui->mainImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete choosecountform; //answerform удаляется внутри него
}

void MainWindow::on_playButton_clicked()
{
    AnswerForm *answerform = new AnswerForm(this);
    SelfTestForm *selfTestForm = new SelfTestForm(this);
    choosecountform = new ChoosecountForm(this);

    answerform->addForm(selfTestForm);
    choosecountform->addForm(answerform); //добавление answerForm, чтобы показать форму позже
    ui->centralwidget->hide();
    choosecountform->show();
}
