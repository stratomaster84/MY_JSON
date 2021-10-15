#ifndef _OGAR_JSON2_H
#define _OGAR_JSON2_H

#include <vector>
#include "json_base.h"

namespace OGAR_Polygon
{

struct federateDescriptor;
struct classesIDDescriptor;
struct informObjDescriptor;
struct addressIterDescriptor;
struct Fed_pairs{
    int ID_Source;
    int ID_Recepient;
};

struct PROXY_DATA : public JSON_BASE
{
    PROXY_DATA() : JSON_BASE(1){}
    virtual ~PROXY_DATA(){clear();}

    std::vector<federateDescriptor> federates;

    virtual void clear(){
        federates.clear();
    }
    virtual bool fill_from_qvariant(const QVariant& tree);
};
struct federateDescriptor{
    std::string federateType;
    std::string NameOfFederate;
    uint8_t requestExitRunStatus = 0;
    std::vector<classesIDDescriptor> vctClassesID;
    std::vector<informObjDescriptor> vctInformObjects;
    std::vector<addressIterDescriptor> vctAdressIteraction;
};

struct  classesIDDescriptor{
    std::string className;
    std::vector<int> vctID;
};

struct informObjDescriptor{
    std::string className;
    std::vector<Fed_pairs> vctPairs;
};

struct addressIterDescriptor{
    std::string className;
    std::vector<Fed_pairs> vctPairs;
};

} // end of namespace OGAR_Polygon

#endif
