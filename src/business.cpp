#include"business.hpp"

Business::Business()
    : id(ID()), location(Vec2())
{}
Business::Business(ID _id, Vec2 _location)
    : id(_id), location(_location)
{}
ID Business::GetID() const {
    return id;
}
Vec2 Business::GetLocation() const {
    return location;
}
gcon::Node * Business::GetNode() {
    return node;
}
void Business::SetNode(gcon::Node * _node) {
    node = _node;
}
void Business::AddStock(gcon::Item item) {
    node->AddItem(item);    
}
void Business::AddRequest(gcon::Item item) {
    node->InitiateRequest(item);
}
void Business::AddSupplyEvent(Event event) {
    supply_events.push_back(event);
}
void Business::AddDemandEvent(Event event) {
    demand_events.push_back(event);
}

void Business::CheckEvents(Time & curtime, RNG * rng) {

    for(
        vec<Event>::iterator it = supply_events.begin();
        it != supply_events.end(); it++
    ) {
        opt<gcon::Item> result = it->Check(rng,curtime);
        if(result.has_value()) {
            AddStock(*result);
        }
    }

    for(
        vec<Event>::iterator it = demand_events.begin();
        it != demand_events.end(); it++
    ) {
        opt<gcon::Item> result = it->Check(rng,curtime);
        if(result.has_value()) {
            AddRequest(*result);
        }
    }

}

BusRtn Business::Update(Time & curtime, RNG * rng) {
    BusRtn rtn = BusRtn::NOCHANGE;

    CheckEvents(curtime,rng);

    return rtn;
}