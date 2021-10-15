#ifndef _OGAR_JSON3_H
#define _OGAR_JSON3_H

#include <vector>
#include "json_base.h"

namespace OGAR_Polygon
{
struct initfiles_st
{
    std::string federateName;
    std::string initData;

    initfiles_st()
    {
        federateName = "";
        initData = "";
    }
    bool fill_from_qvariant(const QVariant& qvar);
};
struct runs_st
{
    int Id;
    int Number;
    std::string desc;
    double finalTime;
    double timeout;

    runs_st()
    {
        finalTime = 600;
        timeout = 120;
        desc = "";
        Id = -1;
        Number = -1;
    }
    bool fill_from_qvariant(const QVariant& qvar);

};
// ЕСЛИ Id или Number ОСТАЛИСЬ "-1" - ОБЪЕКТ НЕ ГОТОВ К РАБОТЕ

struct run_element{
    std::string descData;
    std::vector<initfiles_st> InitFiles;
    std::vector<runs_st> runs;
    bool fill_from_qvariant(const QVariant& qvar);
};
struct RUNS_DATA : public JSON_BASE
{
    RUNS_DATA() : JSON_BASE(2){}
    virtual ~RUNS_DATA(){clear();}

    std::vector<run_element> _list;

    virtual void clear(){
        _list.clear();
    }
    virtual bool fill_from_qvariant(const QVariant& qvar);
};
} // end of namespace OGAR_Polygon

#endif
