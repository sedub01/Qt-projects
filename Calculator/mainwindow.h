#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double getFirstNum(){return firstNum;}
    void setFirstnum(double d){firstNum = d;}

private:
    Ui::MainWindow *ui;
    double firstNum;
    double eps = 1e-6;
    double inf = 10e14;

private slots:
    void digitsNumbers();
    void on_pushButton_dot_clicked();
    void deleteDigit();
    void operations();
    void basicMathOperations();
    void on_pushButton_equal_clicked();
    void switchTable();
    void setConstants();
    void shortOperations();
    void on_pushButton_second_clicked();
    void on_pushButton_degrad_clicked();
    void trigonometricFunctions();
    void putBrackets();
};
#endif // MAINWINDOW_H
