#ifndef _OGAR_JSON_BASE_H
#define _OGAR_JSON_BASE_H

#include <iostream>
#include <QVariant>

namespace OGAR_Polygon
{

struct JSON_BASE{
    JSON_BASE(int _type = -1/*by default*/) : type(_type){}
    virtual ~JSON_BASE(){}

    int type;
    // -1 - not defined
    // 0 - SCENARIO
    // 1 - PROXY_DATA
    // 2 - RUNS_DATA

    virtual void clear() = 0;

    virtual bool parse_from_JSON(const std::string& filename);
    virtual bool fill_from_qvariant(const QVariant& qvar) = 0;

    //virtual bool parse_to_JSON  (const std::string& filename);
    //virtual bool fill_to_qvariant(QVariant& qvar) = 0;
};

} // end of namespace OGAR_Polygon

#endif
