#include"sim.hpp"



/*---------------------------------------------*/
// SIM

Sim::Sim() {
    std::random_device rd;
    rng = RNG(rd());
}
str Sim::GetNetworkAsString() {
    return network.ToString();
}
void Sim::LoadTradeNetwork(str filename) {
    std::ifstream ifs("dat/"+filename);
    nlohmann::json j;
    ifs >> j;

    nlohmann::json jbusinesses = j.at("businesses");
    nlohmann::json jtraders = j.at("traders");

    LoadBusinesses(jbusinesses);
    LoadTraders(jtraders);

    network.RefreshNetwork();
}
void Sim::LoadTraders(nlohmann::json j) {
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        ID id = it.key();
        ID loc = it->at("location");
        vec<ID> itin = it->at("itinerary");
        double speed = it->at("speed");
        bool random_itin = it->at("random_itinerary");
        vec<int> time_at_dest = it->at("time_at_dest");
        Trader trader(id, loc, speed, random_itin, Time(time_at_dest));
        trader.SetItinerary(itin);

        AddTrader(std::move(trader));
    }
}
void Sim::LoadBusinesses(nlohmann::json j) {
    for(
        nlohmann::json::iterator it = j.begin();
        it != j.end(); it++
    ) {
        ID id = it.key();
        vec<double> locvec = it->at("location");
        Business business(id,Vec2(locvec));

        if(it->contains("s_events")) {
            vec<nlohmann::json> sevents = it->at("s_events");
            for(
                vec<nlohmann::json>::iterator sit = sevents.begin();
                sit != sevents.end(); sit++
            ) {
                ID item_id = sit->at("item_id");
                int item_amt = sit->at("item_amt");
                double prob = sit->at("prob");
                vec<int> freq = sit->at("freq");
                int on_hand_max = sit->at("on_hand_max");
                Event event(Item(item_id,item_amt),prob,Time(freq),on_hand_max);
                business.AddSupplyEvent(event);
            }
        }

        if(it->contains("d_events")) {
            vec<nlohmann::json> devents = it->at("d_events");

            for(
                vec<nlohmann::json>::iterator sit = devents.begin();
                sit != devents.end(); sit++
            ) {
                ID item_id = sit->at("item_id");
                int item_amt = sit->at("item_amt");
                double prob = sit->at("prob");
                vec<int> freq = sit->at("freq");
                int on_hand_max = sit->at("on_hand_max");
                Event event(Item(item_id,item_amt),prob,Time(freq),on_hand_max);
                business.AddDemandEvent(event);
            }

        }

        AddBusiness(std::move(business));
    }
}


void Sim::Loop(int iterations) {

    for(int i = 0; i < iterations; i++) {

        network.Update();

        for(
            umap<ID,Business>::iterator it = businesses.begin();
            it != businesses.end(); it++
        ) {
            it->second.Update(time,&rng);
        }

        Business * from_b;
        Business * to_b;
        double dist = 0.0;

        for(
            umap<ID,Trader>::iterator it = traders.begin();
            it != traders.end(); it++
        ) {
            TraderRtn trtn = it->second.Update(time,&rng);
            switch(trtn.type) {
                case TraderRtnType::ARRIVED:
                    network.ActorArrives(it->first,trtn.from,trtn.to);
                    break;
                case TraderRtnType::DEPARTED:
                    network.ActorLeaves(it->first,trtn.from,trtn.to);
                    from_b = GetBusiness(trtn.from);
                    to_b = GetBusiness(trtn.to);
                    dist = from_b->GetLocation().Distance(to_b->GetLocation());
                    it->second.SetTravelTime(dist);
                    break;
                case TraderRtnType::UNCHANGED:
                    break;
                default:
                    break;
            }
        }

        Tick();
    }
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

Business * Sim::GetBusiness(ID id) {
    return &(businesses.at(id));
}
Trader * Sim::GetTrader(ID id) {
    return &(traders.at(id));
}