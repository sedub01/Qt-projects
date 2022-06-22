#ifndef SELFTESTFORM_H
#define SELFTESTFORM_H

#include <QWidget>

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
