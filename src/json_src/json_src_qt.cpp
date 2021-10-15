
#include "json_src.h"

#include <QFile>
#include <QJsonDocument>
namespace OGAR_Polygon {


// from_JSON --true == success
bool JSON_BASE::parse_from_JSON(const std::string &filename){
    QVariant tree;
    QJsonDocument doc;
    QFile file(QString::fromStdString(filename));
    file.open(QFile::ReadOnly);
    if(file.isOpen()){
        doc = QJsonDocument().fromJson(file.readAll());
        tree = doc.toVariant();
        if(!tree.isValid()){
            tree.clear();
            return false;
        }
    }
    else{
        return false;
    }
// работаем с tree и...
    bool no_err = fill_from_qvariant(tree);
    return no_err;

}
bool SCENARIO::fill_from_qvariant(const QVariant& qvar){
// return true == success
    if(qvar.type() != QMetaType::QVariantMap){
        return false;
    }
    bool no_err = true;
    QMap<QString,QVariant> _map = qvar.toMap();
    foreach(QString key, _map.keys()){
        if(key == "file_Description_Proxy" && _map.value(key).type() == QVariant::String)
            file_Description_Proxy = _map.value(key).toString().toStdString();
        else if(key == "file_Description_Run" && _map.value(key).type() == QVariant::String)
            file_Description_Run = _map.value(key).toString().toStdString();
        else if(key == "timeOut" && _map.value(key).type() == QVariant::Double){
            timeOut = _map.value(key).toInt();
        }
        else if(key == "module_FOM_files" && _map.value(key).type() == QMetaType::QVariantList){
// заполняем вектор
            QList<QVariant> _list = _map.value(key).toList();
            std::vector<std::string> _fom_files;
            for(const auto& var : _list){
                if(var.type() != QVariant::String){
                    no_err = false;
                    break;
                }
                _fom_files.push_back(var.toString().toStdString());
            }
            if(!no_err) break;
            module_FOM_files = move(_fom_files);
        }
        else{
            no_err = false;
            break;
        }
    }
    if(!no_err)
        clear();
    return no_err;
}

bool RUNS_DATA::fill_from_qvariant(const QVariant& qvar){
// return true == success
    if(qvar.type() != QMetaType::QVariantList){
        return false;
    }
    bool no_err = true;
    QList<QVariant> qv_list = qvar.toList();
    for(const auto& _list_el : qv_list){
        run_element _el;
        if(!_el.fill_from_qvariant(_list_el)){
            no_err = false;
            break;
        }
        _list.push_back(_el);
    }
    if(!no_err)
        clear();
    return no_err;
}
bool run_element::fill_from_qvariant(const QVariant& qvar){
    // return true == success
    if(qvar.type() != QMetaType::QVariantMap){
        return false;
    }
    bool no_err = true;
    QMap<QString,QVariant> _map = qvar.toMap();
    foreach(QString key, _map.keys()){
        if(key == "descType" && _map.value(key).type() == QVariant::String)
            descData = _map.value(key).toString().toStdString();
        else if(key == "initFiles" && _map.value(key).type() == QMetaType::QVariantList){
            QList<QVariant> qv_list = qvar.toList();
            std::vector<initfiles_st> _list;
            for(const auto& _list_el : qv_list){
                initfiles_st _el;
                if(!_el.fill_from_qvariant(_list_el)){
                    no_err = false;
                    break;
                }
                _list.push_back(_el);
            }
            if(!no_err){
                _list.clear();
                return false;
            }
            InitFiles = move(_list);
        }
        else if(key == "runs" && _map.value(key).type() == QMetaType::QVariantList){
            QList<QVariant> qv_list = qvar.toList();
            std::vector<runs_st> _list;
            for(const auto& _list_el : qv_list){
                runs_st _el;
                if(!_el.fill_from_qvariant(_list_el)){
                    no_err = false;
                    break;
                }
                _list.push_back(_el);
            }
            if(!no_err){
                _list.clear();
                return false;
            }
            runs = move(_list);
        }
        else{
            no_err = false;
            break;
        }
    }
    return no_err;
}
bool initfiles_st::fill_from_qvariant(const QVariant& qvar){
    // return true == success
    if(qvar.type() != QMetaType::QVariantMap){
        return false;
    }
    bool no_err = true;
    QMap<QString,QVariant> _map = qvar.toMap();
    foreach(QString key, _map.keys()){
        if(key == "federateName" && _map.value(key).type() == QVariant::String)
            federateName = _map.value(key).toString().toStdString();
        else if(key == "initData" && _map.value(key).type() == QVariant::String)
            initData = _map.value(key).toString().toStdString();
        else{
            no_err = false;
            break;
        }
    }
    return no_err;
}

bool runs_st::fill_from_qvariant(const QVariant& qvar){
    // return true == success
    if(qvar.type() != QMetaType::QVariantMap){
        return false;
    }
    bool no_err = true;
    QMap<QString,QVariant> _map = qvar.toMap();
    foreach(QString key, _map.keys()){
        if(key == "Id" && _map.value(key).type() == QVariant::Double)
            Id = _map.value(key).toInt();
        else if(key == "Number" && _map.value(key).type() == QVariant::Double)
            Number = _map.value(key).toInt();
        else if(key == "desc" && _map.value(key).type() == QVariant::String)
            desc = _map.value(key).toString().toStdString();
        else if(key == "finalTime" && _map.value(key).type() == QVariant::Double)
            finalTime = _map.value(key).toDouble();
        else if(key == "timeout" && _map.value(key).type() == QVariant::Double)
            timeout = _map.value(key).toDouble();
        else{
            no_err = false;
            break;
        }
    }
    return no_err;
}

bool PROXY_DATA::fill_from_qvariant(const QVariant& qvar){
    return false;
}

} // end of namespace OGAR_Polygon
