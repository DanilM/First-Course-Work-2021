#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "mapmodel.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QDebug>
#include <QStringListModel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainTable->setModel(&mapModel);
    ui->mainTable->verticalHeader()->hide();
    ui->mainTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    mapModel.insertRow(mapModel.rowCount());
}

void MainWindow::on_removeButton_clicked()
{

    mapModel.removeSelected(ui->mainTable->selectionModel()->selectedIndexes());
}

void MainWindow::on_saveTable_triggered()
{
    QString path = QFileDialog::getSaveFileName(0,QObject::tr("Укажите куда сохранить файл"),QDir::homePath(), QObject::tr("CSV файл (*.csv);;Все файлы (*.*)"));
    QFile textFile(path);

    if(path.isEmpty())
        return;

    Parser* parser = new Parser(&textFile, &mapModel);
    parser->writeInFile();

    delete parser;
}

void MainWindow::on_loadTable_triggered()
{
    QString path = QFileDialog::getOpenFileName(0,QObject::tr("Укажите какой файл загрузить"),QDir::homePath(), QObject::tr("CSV файл (*.csv);;Все файлы (*.*)"));
    QFile textFile(path);

    if(path.isEmpty())
        return;

    Parser* parser = new Parser(&textFile, &mapModel);
    parser->readInFile();

    delete parser;
}


