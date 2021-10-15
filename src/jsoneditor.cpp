#include "jsoneditor.h"

#include <QDebug>

JsonEditor::JsonEditor( QObject *parent)
    : QObject(parent),
      path("")
{

}


JsonEditor::~JsonEditor()
{
}

bool JsonEditor::loadJson(QString filename)
{
    path = filename;
    QFile file(filename);
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        doc = QJsonDocument().fromJson(file.readAll());
        return true;
    }
    else
        return false;
}

void JsonEditor::saveJson()
{
    QFile file(path);
    file.open(QFile::WriteOnly);
    if(file.isOpen())
        file.write(doc.toJson());
}


bool JsonEditor::setData(QVariantMap vals, QString part_name)
{
    QJsonObject root = doc.object();
    QJsonObject part = root.value(part_name).toObject();
    QVariantMap::iterator it = vals.begin();
    for(; it != vals.end(); it++)
    {
        QJsonValue val = it.value().toString();
        part.insert(it.key(), val);
    }
    root[part_name] = part;
    doc.setObject(root);
    return true;
}

QVariantMap JsonEditor::getData()
{
    QJsonObject root = doc.object();
    //QJsonObject part = root.value(part_name).toObject();
    QVariantMap params = root.toVariantMap();
    return params;
}

