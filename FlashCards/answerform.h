#ifndef ANSWERFORM_H
#define ANSWERFORM_H

#include "selftestform.h"
#include <QWidget>
#include <vector>

using std::vector;
namespace Ui {
class AnswerForm;
}

class AnswerForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerForm(QWidget *parent = nullptr);
    ~AnswerForm();
    void addForm(SelfTestForm*);

private:
    Ui::AnswerForm *ui;
    SelfTestForm *selfTestForm;

    int index = 1, N/*выбирается пользователем*/;
    int dictSize;
    //массив введенных пользователем слов
    vector<QString> wordArray;
    //массив индексов для избежания повторений
    vector<int> randomInputs;
    //массив для заполнения уникальными числами
    bool *numz;
    //словарный массив
    QString **dictArray;

    void inputWords();
    void readFile();

public slots:
    void slot(QString a);
private slots:
    void gotoTheNextQuestion();
signals:
    void gotoSelfTestForm(vector<QString>& wordArray, vector<int>& randomInputs, QString **dictArray);
};

#endif // ANSWERFORM_H
