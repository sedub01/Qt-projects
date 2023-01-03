#ifndef SELFTESTFORM_H
#define SELFTESTFORM_H

//#include "mainwindow.h"
#include <QWidget>
class MainWindow;

namespace Ui {
class SelfTestForm;
}
using std::vector;

class SelfTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelfTestForm(QWidget *parent = nullptr);
    ~SelfTestForm();

private:
    Ui::SelfTestForm *ui;
    int yesCount;
    int noCount;
    int index;

    vector<QString> wordArray;
    vector<int> randomInputs;
    QVector<std::pair<QString, QString>> dictArray;

    void inputAnswers();
    void reinit();

public slots:
    void gotoSelfTestForm(vector<QString>& wordArray, vector<int>& randomInputs,
                          QVector<std::pair<QString, QString>>& dictArray);
private slots:
    void answer();
signals:
    void goToMainMenu();
};

#endif // SELFTESTFORM_H
