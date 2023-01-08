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
    mChoosecountForm->show();
    ui->centralwidget->hide();
}

void MainWindow::reinit()
{
    if (!mAnswerform){ //connect нужно делать только один раз
        mChoosecountForm = new ChoosecountForm(this);
        mAnswerform = new AnswerForm(this);
        mSelfTestForm = new SelfTestForm(this);
        //Виджеты могут принимать только указатель на QMainWindow, иначе никак

        connect(mChoosecountForm, &ChoosecountForm::nWordsChosen,
                mAnswerform, &AnswerForm::goToAnswerForm);
        connect(mAnswerform, &AnswerForm::gotoSelfTestForm,
                mSelfTestForm, &SelfTestForm::gotoSelfTestForm);
        connect(mSelfTestForm, &SelfTestForm::goToMainMenu,
                this->centralWidget(), &QWidget::show);
    } //mainWindow -> choosecountform -> answerform -> selfTestForm -> mainWindow
}
