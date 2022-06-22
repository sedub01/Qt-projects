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
    //конструктор вызывается единожды
}

AnswerForm::~AnswerForm()
{
    delete ui;
    for (int i = 0; i < dictSize; i++) delete dictArray[i];
    delete dictArray;
    delete selfTestForm;
}

void AnswerForm::slot(QString a)
{
    //слот тоже вызывается один раз
    readFile();
    N = a.toInt();
    //все это заполняется здесь, а не в конструкторе, т.к. там N=0
    wordArray.reserve(N);
    randomInputs.reserve(N);
    inputWords();
}

void AnswerForm::inputWords(){
    ui->wordCountLabel->setText("Слова: " + QString::number(index) + "/" + QString::number(N));

    int random = std::rand() % dictSize;
    for (int i = 0; i < index; i++)
        if (random == randomInputs[i])
            while (random == randomInputs[i])
                random = std::rand() % dictSize;
    randomInputs.push_back(random);

    ui->guessWordLabel->setText(QString::number(index) + ". Переведите слово \"" + dictArray[randomInputs[index-1]][0] + "\": ");
}

void AnswerForm::readFile()
{
    char filePath[] = "C:\\Users\\sedub01\\Desktop\\FlashCards\\words.txt";
    QFile file(filePath); // создаем объект класса QFile (да, только полным именем)
    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные
    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        QMessageBox::critical(this, "Ошибка", "Ты че бля, где файл?\nВведи полное имя файла");
        exit(0);
    }
    data = file.readAll();
    file.close();

    dictSize = countNumberOfStrings(filePath);

    dictArray = new QString*[dictSize];
    for (int i = 0; i < dictSize; i++) dictArray[i] = new QString[2];
    QList<QByteArray> temp = data.split('\n'); //содержится одна строка, ее надо разделить
    for (int i = 0; i < dictSize; i++){
        QByteArray bufferString = temp.takeFirst();
        QStringList bufferArray = QString::fromStdString(bufferString.toStdString()).split(" - ");
        dictArray[i][0] = bufferArray.at(0).trimmed();
        dictArray[i][1] = bufferArray.at(1).trimmed();
    }
    //прочтение файла и запись в массив происходит единожды
}

int countNumberOfStrings(char filePath[]){
    int n = 0;
    FILE* myfile = fopen(filePath, "r+");
    char buffer[100];
    while (fgets(buffer, 100, myfile)) n++; //ok
    fclose(myfile);
    return n;
}

void AnswerForm::on_pushButton_clicked()
{
    if (ui->plainTextEdit->toPlainText() != nullptr){
        wordArray.push_back(ui->plainTextEdit->toPlainText());
        index++;
        ui->plainTextEdit->clear();
        if (index <= N)
            inputWords();
        else{
            ui->plainTextEdit->hide();
            //ui->pushButton->hide(); // скорее, не спрятать, а сделать переход к след. форме
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

