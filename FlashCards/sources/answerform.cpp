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
    player = new QMediaPlayer(this);
    player->setAudioOutput(new QAudioOutput(this));

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
    wordArray.resize(nWords);
    randomInputs.reserve(nWords);
    numz.resize(dictArray.size());
    numz.fill(false);

    ui->plainTextEdit->setFocus();
    inputWords();
}

void AnswerForm::inputWords(){
    ui->wordCountLabel->setText("Слова: " + QString::number(index) +
        "/" + QString::number(wordArray.size()));
    while(true){
        random = std::rand() % dictArray.size();
        if(!numz[random]){
            numz[random] = true;
            randomInputs.push_back(random);
            break;
        }
    }

    ui->guessWordLabel->setText(QString::number(index) + ". Переведите \"" +
        dictArray.at(randomInputs[index-1]).first + "\": ");
}

void AnswerForm::readFile()
{
    char filePath[] = ":/text/words.txt";
    QFile file(filePath); // создаем объект класса QFile
    QString data; // Создаем объект класса QString, куда мы будем считывать данные
    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        QMessageBox::critical(this, "Ошибка", "Ты че бля, где файл?\nВведи полное имя файла");
        exit(0);
    }
    data = file.readAll();
    file.close();

    for (const auto &stringFromFile : data.split('\n')){
        const auto bufferArray = stringFromFile.split(" - ");
        dictArray.append({bufferArray.at(0).trimmed(), bufferArray.at(1).trimmed()});
    }
}

void AnswerForm::reinit()
{
    wordArray.clear();
    randomInputs.clear();
    numz.clear();
    dictArray.clear();
    index = 1;
    ui->plainTextEdit->show();
    ui->wordCountLabel->show();
    ui->speakerButton->show();
}

void AnswerForm::gotoTheNextQuestion()
{
    if (!ui->plainTextEdit->text().isEmpty()){
        wordArray[index - 1] = ui->plainTextEdit->text();
        index++;
        ui->plainTextEdit->clear();
        if (index <= (int)wordArray.size())
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
        emit gotoSelfTestForm(wordArray, randomInputs, dictArray);
        //вектор передается по ссылке
    }
}

void AnswerForm::pronounceSpeaking() //speaker должен знать значение random'а
{
    const QString pathRegex = ":/pronouncings/pronouncings/%1.mp3";
    const QString path = pathRegex.arg(QString::number(random + 1));
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
    player->setSource(QUrl(source));
    player->play();
}
