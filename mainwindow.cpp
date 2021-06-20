#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("NotepadQT");
    this->setCentralWidget(ui->textEdit);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(on_actionNew_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(on_actionOpen_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(on_actionUndo_triggered()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(on_actionRedo_triggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    currentFile = "";
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");

    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly |QFile::Text )) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;

    }
    setWindowTitle("NotepadQT - " + filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    if (currentFile.isEmpty()) {
        QString filename = QFileDialog::getSaveFileName(this, "Save as");
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly |QFile::Text )) {
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
            return;
        }
        currentFile = filename;
        setWindowTitle("NotepadQT - " + filename);
        QTextStream out(&file) ;
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
    } else {
        QFile file(currentFile);
        if(!file.open(QIODevice::WriteOnly |QFile::Text )) {
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
            return;
        }
        QTextStream out(&file) ;
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaster_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionLogin_triggered()
{
   ui->textEdit->setTextColor(Qt::cyan);
   ui->textEdit->autoFillBackground();
   ui->textEdit->setTextBackgroundColor(Qt::magenta);
   ui->textEdit->append("\nLie");

}
