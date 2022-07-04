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
    void addForm(MainWindow*);

private:
    Ui::SelfTestForm *ui;
    MainWindow *mainWindow;
    int yesCount = 0, noCount = 0, index = 1;

    vector<QString> wordArray;
    vector<int> randomInputs;
    QString** dictArray;

    void inputAnswers();

public slots:
    void slot(vector<QString>& wordArray, vector<int>& randomInputs, QString **dictArray);
private slots:
    void answer();
};

#endif // SELFTESTFORM_H
