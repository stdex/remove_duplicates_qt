#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processSlot() {
    //QString kml = ui->textBrowser->toPlainText();
    //QStringList lines = kml.split( "\n" );
    //ui->textBrowser->clear();
    //ui->textBrowser->append( QString( "%1").arg( words[1].replace( "</", "" ) ) );

    stringList_out.clear();

    foreach (QString a, stringList_1)
    {
        QString not_found_str = "";
        foreach (QString b, stringList_2)
        {
            int matches = matchingStrings(a, b);
            qDebug() << matches;
            if (matches > 0)
            {
                not_found_str = "";
                break;
                // do something fancy
            }
            else {
                not_found_str = a;
                //qDebug() << not_found_str;
            }
        }

        if(not_found_str != "") {
            stringList_out.append(not_found_str);
        }
    }

    QFile fOut("file.txt");
    if (fOut.open(QFile::WriteOnly | QFile::Text)) {

        QTextStream s(&fOut);
        for (int i = 0; i < stringList_out.size(); ++i) {
            s << stringList_out.at(i) << '\n';
        }

        QString out;
        out = stringList_out.join("\n");
        ui->textBrowser->clear();
        ui->textBrowser->append( out );
     }

     fOut.close();

}

void MainWindow::loadFileSlot() {

    ui->textBrowser->clear();
    stringList_1.clear();

    QString fileName = QFileDialog::getOpenFileName(this);
    ui->lineEdit->setText( fileName );

    QFile file( fileName );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->textBrowser->append( line );
        if (line.isNull()) {
             break;
        }
        else {
            stringList_1.append(line);
        }
    }

}

void MainWindow::loadFileSlot_2() {

    ui->textBrowser_2->clear();
    stringList_2.clear();

    QString fileName = QFileDialog::getOpenFileName(this);
    ui->lineEdit_2->setText( fileName );

    QFile file( fileName );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->textBrowser_2->append( line );
        if (line.isNull()) {
             break;
        }
        else {
            stringList_2.append(line);
        }
    }

}


int MainWindow::matchingStrings(QString str1, QString str2)
{
    int matches = 0;
    int minSize = str1.size() < str2.size() ? str1.size() : str2.size();
    int maxSize = str1.size() > str2.size() ? str1.size() : str2.size();
    for (int pos = 0; pos < minSize; ++pos)
    {
        if (str1.at(pos) == str2.at(pos)) ++matches;
    }

    if(matches == maxSize) {
        return matches;
    }
    else {
        return 0;
    }


}
