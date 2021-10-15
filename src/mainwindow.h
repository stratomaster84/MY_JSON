#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QJsonDocument>

#include "json_src/json_src.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool fillItem(QStandardItem *item,const QVariant& obj, const QString& name);

private:
    Ui::MainWindow *ui;
    QVariant tree;

    OGAR_Polygon::JSON_BASE *json_obj;

public slots:
    void slot_fromJSON();
    void slot_toJSON();
};

#endif // MAINWINDOW_H
