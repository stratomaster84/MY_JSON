#ifndef JSONEDITOR_H
#define JSONEDITOR_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>


class JsonEditor : public QObject
{
    Q_OBJECT
public:
    explicit JsonEditor(QObject *parent = nullptr);
    virtual ~JsonEditor();

    void saveJson();
    bool loadJson(QString filename);
    QVariantMap getData();
    bool setData(QVariantMap vals, QString part_name);

signals:


public:
    QJsonDocument doc;
    QString path;

public slots:
};

#endif // JSONEDITOR_H
