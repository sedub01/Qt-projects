#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QAudioOutput>
#include <QMediaPlayer>

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
    choosecountform = nullptr;
}

void MainWindow::on_playButton_clicked()
{
    if (!answerform) answerform = new AnswerForm(this);
    if (!selfTestForm) selfTestForm = new SelfTestForm(this);
    if (!choosecountform) choosecountform = new ChoosecountForm(this);

//    QAudioOutput *audioOutput = new QAudioOutput(this);
//    QMediaPlayer *player = new QMediaPlayer();
//    player->setAudioOutput(audioOutput);
//    audioOutput->setVolume(50);
//    player->setSource(QUrl("qrc:/pronouncings/pronouncings/12.mp3"));
//    player->play();

    selfTestForm->addForm(this);
    answerform->addForm(selfTestForm);
    choosecountform->addForm(answerform); //добавление answerForm, чтобы показать форму позже
    ui->centralwidget->hide();
    choosecountform->show();
}
