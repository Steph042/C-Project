#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QSaveFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = "/home/Nuovo";
    QFile file(fileName);

    bool openOk = file.open(QIODevice::ReadWrite);
    if (!openOk)
    {
       std::cerr << "Inpossibile creare file" << std::endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
        filename = QFileDialog::getOpenFileName(this,
                   tr("Apri File"),"/home",
                   "Text File (*.rtf)");

        QFile file(filename);

        bool openOk = file.open(QIODevice::ReadWrite);
        if (!openOk)
        {
            std::cerr << "Impossibile aprire file" << std::endl;
        }

        QTextStream in(&file);

        ui->textEdit->setText(in.readAll());
        ui->textEdit->setEnabled(1);
        ui->pushButton_7->setDisabled(1);
}

void MainWindow::on_textEdit_selectionChanged()
{
    ui->spinBox->setEnabled(1);
    ui->pushButton_3->setEnabled(1);
    ui->pushButton_4->setEnabled(1);
    ui->pushButton_5->setEnabled(1);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->textEdit->setFontPointSize(arg1);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->textEdit->fontInfo().bold() == false){
        ui->textEdit->setFontWeight(75);
    }

    if(ui->textEdit->fontInfo().bold() == true)
        ui->textEdit->setFontWeight(50);

}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->textEdit->fontInfo().italic() == false){
        ui->textEdit->setFontItalic(true);
    } else
        ui->textEdit->setFontItalic(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->textEdit->fontInfo().underline() == false){
        ui->textEdit->setFontUnderline(true);
    } else
        ui->textEdit->setFontUnderline(false);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString fileName2 = QFileDialog::getSaveFileName(this,
                        tr("Save file"), "",
                        tr("Text file (*.rtf);;All Files (*)"));

    if (fileName2.isEmpty())
    {
        std::cerr << "Inserire nome" << std::endl;
        return;
    }
    QSaveFile file(fileName2);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    out << ui->textEdit->toHtml() << Qt::endl;
    file.commit();
}

void MainWindow::on_textEdit_textChanged()
{
    ui->pushButton_7->setEnabled(1);
}

void MainWindow::on_pushButton_7_clicked()
{
    QSaveFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    out << ui->textEdit->toHtml() << Qt::endl;
    file.commit();
}


