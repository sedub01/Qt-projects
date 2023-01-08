#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <cstdlib>
#include "headers/answerform.h"
#include "ui_answerform.h"

AnswerForm::AnswerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerForm)
{
    ui->setupUi(this);
    std::srand(std::time(nullptr));
    mPlayer = new QMediaPlayer(this);
    mPlayer->setAudioOutput(new QAudioOutput(this));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(gotoTheNextQuestion()));
    connect(ui->plainTextEdit, SIGNAL(returnPressed()), this, SLOT(gotoTheNextQuestion()));
    connect(ui->speakerButton, &QPushButton::clicked, this, &AnswerForm::pronounceSpeaking);
    for (const auto& button: {ui->speakerButton, ui->pushButton}){
        connect(button, &QPushButton::clicked, ui->plainTextEdit, [this](){
            ui->plainTextEdit->setFocus();
        });
    }
    //конструктор, slot(), прочтение файла и запись в массив вызываются единожды
}

AnswerForm::~AnswerForm()
{
    delete ui;
    //Если объект - QObject и он принимает this, его можно не удалять
}

void AnswerForm::goToAnswerForm(int nWords)
{
    show();
    reinit();
    readFile();
    //все это заполняется здесь, а не в конструкторе, т.к. там N=0
    //reserve просто резервирует память (после вызова метода размер == 0)
    //resize уже изменяет размер массива (т.е. размер == N)
    mWordArray.resize(nWords);
    mRandomInputs.reserve(nWords);
    mNumz.resize(mDictArray.size());
    mNumz.fill(false);

    ui->plainTextEdit->setFocus();
    inputWords();
}

void AnswerForm::inputWords(){
    ui->wordCountLabel->setText("Слова: " + QString::number(mCurrentIndex) +
        "/" + QString::number(mWordArray.size()));
    while(true){
        mRandomIndex = std::rand() % mDictArray.size();
        if(!mNumz[mRandomIndex]){
            mNumz[mRandomIndex] = true;
            mRandomInputs.push_back(mRandomIndex);
            break;
        }
    }

    ui->guessWordLabel->setText(QString::number(mCurrentIndex) + ". Переведите \"" +
        mDictArray.at(mRandomInputs[mCurrentIndex-1]).first + "\": ");
}

void AnswerForm::readFile()
{
    const char filePath[] = ":/text/words.txt";
    QFile file(filePath); // создаем объект класса QFile
    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        QMessageBox::critical(this, "Ошибка", "Ты че бля, где файл?\nВведи полное имя файла");
        exit(0);
    }
    // Создаем объект класса QString, куда мы будем считывать данные
    const QString data = file.readAll();
    file.close();

    for (const auto &stringFromFile : data.split('\n')){
        const auto bufferArray = stringFromFile.split(" - ");
        mDictArray.append({bufferArray.at(0).trimmed(), bufferArray.at(1).trimmed()});
    }
}

void AnswerForm::reinit()
{
    mWordArray.clear();
    mRandomInputs.clear();
    mNumz.clear();
    mDictArray.clear();
    mCurrentIndex = 1;
    ui->plainTextEdit->show();
    ui->wordCountLabel->show();
    ui->speakerButton->show();
}

void AnswerForm::gotoTheNextQuestion()
{
    if (!ui->plainTextEdit->text().isEmpty()){
        mWordArray[mCurrentIndex - 1] = ui->plainTextEdit->text();
        mCurrentIndex++;
        ui->plainTextEdit->clear();
        if (mCurrentIndex <= (int)mWordArray.size())
            inputWords();
        else{
            ui->plainTextEdit->hide();
            ui->wordCountLabel->hide();
            ui->speakerButton->hide();
            ui->guessWordLabel->setText("Теперь переходим к проверке");
        }
    }
    else if (!ui->plainTextEdit->isHidden())
        QMessageBox::critical(this, "Ошибка", "Здесь ничего нет!");
    else{
        hide();
        emit gotoSelfTestForm(mWordArray, mRandomInputs, mDictArray);
        //вектор передается по ссылке
    }
}

void AnswerForm::pronounceSpeaking() //speaker должен знать значение random'а
{
    const QString pathRegex = ":/pronouncings/pronouncings/%1.mp3";
    const QString path = pathRegex.arg(QString::number(mRandomIndex + 1));
    const QFileInfo checkFile(path);
    QString source = "qrc" + path;

    if (!checkFile.exists()){
        int unfoundRandom = std::rand() % 3 - 3;
        source = "qrc" + pathRegex.arg(QString::number(unfoundRandom));
        const auto thread = new QThread();
        connect(thread, &QThread::started, this, [](){
            QMessageBox msgBox;
            msgBox.setIconPixmap(QPixmap()); //нужно, чтобы не производился системный звук
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Извини, пока что нет \nзвукового сопровождения \nдля этой фразы");
            msgBox.exec();
        });
        thread->start();
        QTimer::singleShot(1, this, [thread](){
            thread->quit();
        });
    }
    mPlayer->setSource(QUrl(source));
    mPlayer->play();
}
