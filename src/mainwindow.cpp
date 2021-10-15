#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    json_obj(nullptr)
{
    ui->setupUi(this);

    connect(ui->fromjson_but, SIGNAL(clicked()),SLOT(slot_fromJSON()));
    connect(ui->tojson_but,   SIGNAL(clicked()),SLOT(slot_toJSON()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(json_obj != nullptr) delete json_obj;
    json_obj = nullptr;
}


bool MainWindow::fillItem(QStandardItem *item,const QVariant& obj, const QString& name = "")
{
    QString _str = "";
    if(!obj.isValid())
        return false;
    if(obj.isNull()){
        if(name != "")
            _str = name + " (литерал): null";
        else
            _str = "(литерал): null";
        item->appendRow(new QStandardItem(_str));
        return true;
    }
    if(obj.type() == QVariant::String){
        if(name != "")
            _str = name + " (строка): ";
        else
            _str = "(строка): ";
        item->appendRow(new QStandardItem(_str + obj.toString()));
        return true;
    }
    if(obj.type() == QVariant::Double){
        if(name != "")
            _str = name + " (число): ";
        else
            _str = "(число): ";
        item->appendRow(new QStandardItem(_str + obj.toString()));
        return true;
    }
    if(obj.type() == QVariant::Bool){
        if(name != "")
            _str = name + " (литерал): ";
        else
            _str = "(литерал): ";

        item->appendRow(new QStandardItem(_str + obj.toString()));
        return true;
    }
    if(obj.type() == QMetaType::QVariantList){
        QList<QVariant> _list = obj.toList();

        if(name != "")
            _str = name + " (массив)";
        else
            _str = "(массив)";

        QStandardItem *newitem = new QStandardItem(_str);
        int i = 0;
        for(const auto& var : _list){
            fillItem(newitem, var, QString::number(i));
            ++i;
        }
        item->appendRow(newitem);
        return true;
    }
    if(obj.type() == QMetaType::QVariantMap){
        QMap<QString,QVariant> _map = obj.toMap();

        if(name != "")
            _str = name + " (объект)";
        else
            _str = "(объект)";
        QStandardItem *newitem = new QStandardItem(_str);

        foreach(QString key, _map.keys()){
            QVariant _value = _map.value(key);
            fillItem(newitem, _value,key);
        }
        item->appendRow(newitem);
        return true;
    }
    return false;
}


void MainWindow::slot_fromJSON(){
    QMessageBox msgBox;
    ui->file_name->setText(
                QFileDialog::getOpenFileName(nullptr,"Выберите файл json для загрузки данных",".","*.json")
    );

    OGAR_Polygon::JSON_BASE *new_obj;

    if(ui->scenario_item->isChecked()){
        new_obj= new OGAR_Polygon::SCENARIO;
    }else if(ui->proxy_item->isChecked()){
        new_obj= new OGAR_Polygon::PROXY_DATA;
    }else{
        new_obj= new OGAR_Polygon::RUNS_DATA;
    }

    if(!new_obj->parse_from_JSON(ui->file_name->text().toStdString())){
        if(new_obj->type == 0) msgBox.setText("JSON-файл не является файлом сценария");
        if(new_obj->type == 1) msgBox.setText("JSON-файл не является файлом прокси");
        if(new_obj->type == 2) msgBox.setText("JSON-файл не является файлом прогонов");

        delete new_obj;

        msgBox.exec();
    }
    else{
        if(json_obj != nullptr) delete json_obj;
        json_obj = new_obj;
    }

// В ЛЮБОМ СЛУЧАЕ ВЫВОДИМ ДОКУМЕНТ СПОСОБАМИ QT
    {
        QJsonDocument doc;
        QFile file(ui->file_name->text());
        file.open(QFile::ReadOnly);
        if(file.isOpen()){
            doc = QJsonDocument().fromJson(file.readAll());
            tree = doc.toVariant();
            if(!tree.isValid()){
                msgBox.setText("Файл не является корректным json");
                msgBox.exec();
                return;
            }
        }
        else{
            msgBox.setText("Невозможно открыть файл");
            msgBox.exec();
            return;
        }
    }

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *root = model->invisibleRootItem();

    if(!fillItem(root,tree)){
        msgBox.setText("При загрузке данных произошла ошибка");
        msgBox.exec();
        return;
    }
    ui->json_view->setModel(model);
}

void MainWindow::slot_toJSON(){

}
