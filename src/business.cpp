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
void Business::AddConsumeEvent(Event event) {
    consume_events.push_back(event);
}
int Business::GetAmountOfItemInStock(ID item_id) {
    return node->GetAmountOfItemInStock(item_id);
}

void Business::CheckEvents(Time & curtime, RNG * rng) {

    for(
        vec<Event>::iterator it = supply_events.begin();
        it != supply_events.end();
    ) {
        opt<gcon::Item> result = it->Check(rng,curtime);
        if(result.has_value()) {
            int amt_in_stock = GetAmountOfItemInStock(result->GetID());
            if(amt_in_stock < it->GetOnHandMax()) {
                AddStock(*result);
            }
            it = supply_events.erase(it);
        } else {
            it++;
        }
    }

    for(
        vec<Event>::iterator it = demand_events.begin();
        it != demand_events.end(); it++
    ) {
        opt<gcon::Item> result = it->Check(rng,curtime);
        if(result.has_value()) {
            int amt_in_stock = GetAmountOfItemInStock(result->GetID());
            if(amt_in_stock < it->GetOnHandMax()) {
                AddRequest(*result);
            }
            it = demand_events.erase(it);
        } else {
            it++;
        }
    }

    for(
        vec<Event>::iterator it = consume_events.begin();
        it != consume_events.end(); it++
    ) {
        opt<gcon::Item> result = it->Check(rng,curtime);
        if(result.has_value()) {

            int amt_in_stock = GetAmountOfItemInStock(result->GetID());
            if(amt_in_stock > 0) {
                AddStock(*result);
            }
            it = demand_events.erase(it);
        } else {
            it++;
        }
    }

}

BusRtn Business::Update(Time & curtime, RNG * rng) {
    BusRtn rtn = BusRtn::NOCHANGE;

    CheckEvents(curtime,rng);

    return rtn;
}