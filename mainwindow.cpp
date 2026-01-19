#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    currentFile = QFileDialog::getOpenFileName(this, "Abrir");
    if (currentFile.isEmpty())
        return;
    QFile file(currentFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
    file.close();
}

void MainWindow::on_actionSave_triggered() {
    if (currentFile.isEmpty()) {
        on_actionSaveAs_triggered();
        return;
    }
    QFile file(currentFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "error guardar", file.errorString());
        return;
    }
    QTextStream io(&file);
    io << ui->textEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_actionSaveAs_triggered(){
    QFile file(QFileDialog::getSaveFileName(this, "save as"));
    if (file.fileName().isEmpty())
        return;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "error al abrir el archivo", file.errorString());
        return;
    }
    QTextStream io(&file);
    io << ui->textEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_actionCopy_triggered(){
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered(){
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered(){
    ui->textEdit->paste();
}

void MainWindow::on_actionAbout_triggered(){
    QMessageBox::aboutQt(this,"Qt");
}

void MainWindow::on_actionClose_triggered(){
    close();
}

void MainWindow::on_actionType_triggered(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(!ok)
        return;
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionColor_triggered(){
    ui->textEdit->setTextColor(QColorDialog::getColor(Qt::white,this));
}


void MainWindow::on_actionBackgroundColor_triggered(){
    ui->textEdit->setPalette(QPalette(QColorDialog::getColor(Qt::white,this)));
}

