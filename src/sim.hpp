#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"gtime.hpp"
#include"business.hpp"
#include"trader.hpp"

using namespace gcon;

/*---------------------------------------------*/



/*---------------------------------------------*/

class Sim {
private:
    Time time;
    Network network;
    umap<ID,Business> businesses;
    umap<ID,Trader> traders;
public:
    Sim();
    void BuildTradeNetwork();
    void Loop();
    void Tick();

    void AddBusiness(Business business);
    void AddTrader(Trader trader);

};