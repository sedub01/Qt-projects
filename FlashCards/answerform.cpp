#include <QMessageBox>
#include <QFile>
#include <cstdlib>
#include "answerform.h"
#include "ui_answerform.h"

AnswerForm::AnswerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerForm)
{
    ui->setupUi(this);
    std::srand(std::time(nullptr));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(gotoTheNextQuestion()));
    connect(ui->plainTextEdit, SIGNAL(returnPressed()), this, SLOT(gotoTheNextQuestion()));
    //конструктор, slot(), прочтение файла и запись в массив вызываются единожды
}

AnswerForm::~AnswerForm()
{
    delete ui;
    for (int i = 0; i < dictSize; i++) delete dictArray[i];
    delete dictArray;
    delete selfTestForm;
    delete[] numz;
}

void AnswerForm::slot(QString a)
{
    readFile();
    N = a.toInt();
    //все это заполняется здесь, а не в конструкторе, т.к. там N=0
    wordArray.reserve(N);
    randomInputs.reserve(N);
    numz = new bool[dictSize]{false, };

    ui->plainTextEdit->setFocus();
    inputWords();
}

void AnswerForm::inputWords(){
    ui->wordCountLabel->setText("Слова: " + QString::number(index) + "/" + QString::number(N));

    int random;
//  randomInputs.push_back(std::rand() % dictSize); - вариант с повторениями

    while(true){
        random = std::rand() % dictSize;
        if(!numz[random]){
            numz[random] = true;
            randomInputs.push_back(random);
            break;
        }
    }

    ui->guessWordLabel->setText(QString::number(index) + ". Переведите \"" + dictArray[randomInputs[index-1]][0] + "\": ");
}

void AnswerForm::readFile()
{
    char filePath[] = ":/text/words.txt";
    QFile file(filePath); // создаем объект класса QFile (да, только полным именем)
    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные
    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        QMessageBox::critical(this, "Ошибка", "Ты че бля, где файл?\nВведи полное имя файла");
        exit(0);
    }
    data = file.readAll();    
    file.close();

    dictSize = data.count("\n") + 1;

    dictArray = new QString*[dictSize];
    for (int i = 0; i < dictSize; i++) dictArray[i] = new QString[2];
    int i = 0;
    for (QByteArray temp : data.split('\n')){
        QStringList bufferArray = QString::fromStdString(temp.toStdString()).split(" - ");
        dictArray[i][0] = bufferArray.at(0).trimmed();
        dictArray[i][1] = bufferArray.at(1).trimmed();
        i++;
    }
}

void AnswerForm::gotoTheNextQuestion()
{
    if (ui->plainTextEdit->text() != nullptr){
        wordArray.push_back(ui->plainTextEdit->text());
        index++;
        ui->plainTextEdit->clear();
        if (index <= N)
            inputWords();
        else{
            ui->plainTextEdit->hide();
            ui->wordCountLabel->hide();
            ui->guessWordLabel->setText("Теперь переходим к проверке");
        }
    }
    else if (!ui->plainTextEdit->isHidden())
        QMessageBox::critical(this, "Ошибка", "Здесь ничего нет!");
    else{
        hide();
        selfTestForm->show();
        connect(this, &AnswerForm::gotoSelfTestForm, this->selfTestForm, &SelfTestForm::slot);
        emit gotoSelfTestForm(wordArray, randomInputs, dictArray); //отправление к слоту
        //вектор передается по ссылке
    }
}

void AnswerForm::addForm(SelfTestForm* selfTestForm){
    this->selfTestForm = selfTestForm;
}

