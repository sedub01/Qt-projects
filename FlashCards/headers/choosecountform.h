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

    void addForm(AnswerForm* answerform);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChoosecountForm *ui;
    AnswerForm *answerform;
signals:
    void signal(QString);
};

#endif // CHOOSECOUNTFORM_H
