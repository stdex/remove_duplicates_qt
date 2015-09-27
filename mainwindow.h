#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void processSlot();
    void loadFileSlot();
    void loadFileSlot_2();

private:
    Ui::MainWindow *ui;
    QStringList stringList_1;
    QStringList stringList_2;
    QStringList stringList_out;
    int matchingStrings(QString str1, QString str2);
};

#endif // MAINWINDOW_H
