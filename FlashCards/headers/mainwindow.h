#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "answerform.h"
#include "choosecountform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void playButtonClicked();

private:
    Ui::MainWindow *ui;
    //это на тот случай, если игрок захочет играть не один раз
    AnswerForm *mAnswerform = nullptr;
    SelfTestForm *mSelfTestForm = nullptr;
    ChoosecountForm *mChoosecountForm = nullptr;

    void reinit();
};
#endif // MAINWINDOW_H
