#ifndef ANSWERFORM_H
#define ANSWERFORM_H

#include "selftestform.h"
#include <QWidget>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QTimer>
#include <QThread>
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

private:
    Ui::AnswerForm *ui;

    int index;
    //массив введенных пользователем слов
    vector<QString> wordArray;
    //массив индексов для избежания повторений
    vector<int> randomInputs;
    //массив для заполнения уникальными числами
    QVector<bool> numz;
    //структура, хранящая абсолютно все переводы из файла
    QList<std::pair<QString, QString>> dictArray;
    int random;
    QMediaPlayer *player;

    void inputWords();
    void readFile();
    void reinit();

public slots:
    void goToAnswerForm(int);
private slots:
    void gotoTheNextQuestion();
    void pronounceSpeaking();

signals:
    void gotoSelfTestForm(vector<QString>& wordArray, vector<int>& randomInputs,
                          QVector<std::pair<QString, QString>>& dictArray);
};

#endif // ANSWERFORM_H
