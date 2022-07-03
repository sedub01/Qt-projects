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
    void on_playButton_clicked();

private:
    Ui::MainWindow *ui;
    //AnswerForm *answerform;
    ChoosecountForm *choosecountform;
};
#endif // MAINWINDOW_H
