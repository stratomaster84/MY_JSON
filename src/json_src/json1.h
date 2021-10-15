#ifndef _OGAR_JSON1_H
#define _OGAR_JSON1_H

#include <vector>
#include "json_base.h"

namespace OGAR_Polygon
{

// НАЗВАНИЕ
struct SCENARIO : public JSON_BASE
{
    SCENARIO() : JSON_BASE(0){}
    virtual ~SCENARIO(){clear();}

    std::vector<std::string> module_FOM_files;
    std::string file_Description_Proxy;
    std::string file_Description_Run;
    int timeOut;

    virtual void clear(){
        module_FOM_files.clear();
        file_Description_Proxy.clear();
        file_Description_Run.clear();
    }
    virtual bool fill_from_qvariant(const QVariant& qvar);
};

} // end of namespace OGAR_Polygon

#endif
