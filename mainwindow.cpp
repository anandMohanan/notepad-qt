#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
     QShortcut *shortcutforExit = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);
     QObject::connect(shortcutforExit,    &QShortcut::activated,
                          this,        &MainWindow::on_actionexit_triggered);

     QShortcut *shortcutforNew = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this);
     QObject::connect(shortcutforNew,    &QShortcut::activated,
                          this,        &MainWindow::on_actionnew_triggered);

     QShortcut *shortcutforOpen = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
     QObject::connect(shortcutforOpen,    &QShortcut::activated,
                          this,        &MainWindow::on_actionopen_triggered);
     QShortcut *shortcutforUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
     QObject::connect(shortcutforUndo,    &QShortcut::activated,
                          this,        &MainWindow::on_actionundo_triggered);

     QShortcut *shortcutforRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
     QObject::connect(shortcutforRedo,    &QShortcut::activated,
                          this,        &MainWindow::on_actionredo_triggered);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionnew_triggered()
{
    currentfile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionopen_triggered()
{
        QString filename = QFileDialog::getOpenFileName(this,"open file");
        QFile file(filename);
        currentfile = filename;
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,"warning","Cannot open file: " + file.errorString());
            return;
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
}


void MainWindow::on_actionsave_as_triggered()
{
        QString filename = QFileDialog::getSaveFileName(this,"save file as");
        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"warning","Cannot save file: " + file.errorString());
            return;
        }
        currentfile = filename;
        setWindowTitle(filename);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
}


void MainWindow::on_actionprint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("");
    QPrintDialog pDialog(&printer,this);
if(pDialog.exec() == QDialog::Rejected){
QMessageBox::warning(this,"warning","cannot access printer");
return;
}
ui->textEdit->print(&printer);

}


void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionredo_triggered()
{
ui->textEdit->redo();
}


void MainWindow::on_actionsave_triggered()
{
    setWindowTitle(currentfile);
    if(currentfile.isEmpty()){
        on_actionsave_as_triggered();
    };
    QFile file(currentfile);
    QTextStream out(&currentfile);
    QString text = ui->textEdit->toPlainText();
    out << text;
}

