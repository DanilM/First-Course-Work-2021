#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractItemModel>
#include <QHeaderView>
#include <QMainWindow>
#include "mapmodel.h"
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_saveTable_triggered();

    void on_loadTable_triggered();

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;
    MapModel mapModel;
};

#endif // MAINWINDOW_H
