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
    connect(ui->playButton, &QPushButton::clicked,
            this, &MainWindow::playButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playButtonClicked()
{
    reinit();
    choosecountform->show();
    ui->centralwidget->hide();
}

void MainWindow::reinit()
{
    if (!answerform){ //connect нужно делать только один раз
        choosecountform = new ChoosecountForm(this);
        answerform = new AnswerForm(this);
        selfTestForm = new SelfTestForm(this);
        //Виджеты могут принимать только указатель на QMainWindow, иначе никак

        connect(choosecountform, &ChoosecountForm::nWordsChosen,
                answerform, &AnswerForm::goToAnswerForm);
        connect(answerform, &AnswerForm::gotoSelfTestForm,
                selfTestForm, &SelfTestForm::gotoSelfTestForm);
        connect(selfTestForm, &SelfTestForm::goToMainMenu,
                this->centralWidget(), &QWidget::show);
    } //mainWindow -> choosecountform -> answerform -> selfTestForm -> mainWindow
}
