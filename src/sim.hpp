#pragma once

#include<fstream>

#include"defs.hpp"
#include"gamecon.hpp"
#include"gtime.hpp"
#include"business.hpp"
#include"trader.hpp"

#include"json.hpp"

using namespace gcon;

/*---------------------------------------------*/



/*---------------------------------------------*/

class Sim {
private:
    RNG rng;
    Time time;
    Network network;
    umap<ID,Business> businesses;
    umap<ID,Trader> traders;
public:
    Sim();

    str GetNetworkAsString();

    void LoadTradeNetwork(str filename);
    void LoadTraders(nlohmann::json j);
    void LoadBusinesses(nlohmann::json j);
    void Loop(int iterations);
    void Tick();

    void AddBusiness(Business business);
    void AddTrader(Trader trader);

    Business * GetBusiness(ID id);
    Trader * GetTrader(ID id);

};