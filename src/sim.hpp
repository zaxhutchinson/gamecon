#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"gtime.hpp"

using namespace gcon;

/*---------------------------------------------*/



/*---------------------------------------------*/

class Sim {
private:
    Time time;
    TradeNetwork tn;
public:
    Sim();
    void BuildTradeNetwork();
    void Loop();
    void Tick();

};