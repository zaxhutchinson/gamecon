#include"business.hpp"

Business::Business()
    : id(ID()), location(Vec2())
{}
Business::Business(Vec2 _location, gcon::Node _node)
    : location(_location), node(_node)
{}
ID Business::GetID() const {
    return node.GetID();
}
Vec2 Business::GetLocation() const {
    return location;
}
void Business::AddStock(gcon::Item item) {
    node.AddItem(item);    
}
void Business::AddRequest(gcon::Item item) {
    node.InitiateRequest(item);
}
void Business::AddSupplyEvent(Event event) {
    supply_events.push_back(event);
}
void Business::AddDemandEvent(Event event) {
    demand_events.push_back(event);
}

void Business::CheckEvents(RNG * rng, Time & curtime) {

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