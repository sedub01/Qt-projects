#ifndef CHOOSECOUNTFORM_H
#define CHOOSECOUNTFORM_H

#include <QWidget>
#include "answerform.h"

namespace Ui {
class ChoosecountForm;
}

class ChoosecountForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosecountForm(QWidget *parent = nullptr);
    ~ChoosecountForm();

private slots:
    void goToAnswerForm();

private:
    Ui::ChoosecountForm *ui;
signals:
    void nWordsChosen(int);
};

#endif // CHOOSECOUNTFORM_H
