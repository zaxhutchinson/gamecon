#include"sim.hpp"



/*---------------------------------------------*/
// SIM

Sim::Sim() {

}
void Sim::BuildTradeNetwork() {

}
void Sim::Loop() {


    Tick();
}
void Sim::Tick() {


    // Increment the time.
    time.Tick();
}

void Sim::AddBusiness(Business business){
    uptr<Node> n = std::make_unique<Node>(business.GetID());
    network.RegisterNode(std::move(n));
    business.SetNode(network.GetNode(business.GetID()));
    businesses.emplace(business.GetID(), business);
}
void Sim::AddTrader(Trader trader) {
    uptr<Actor> t = std::make_unique<Actor>(trader.GetID());
    network.RegisterActor(std::move(t));
    trader.SetActor(network.GetActor(trader.GetID()));
    traders.emplace(trader.GetID(), trader);
}