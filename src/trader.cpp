#include"trader.hpp"

Trader::Trader() {

}
Trader::Trader(ID _location, gcon::Actor * _actor)
    : location(_location), actor(_actor)
{}
ID Trader::GetID() const {
    return actor->GetID();
}
gcon::Actor * Trader::GetActor() {
    return actor;
}
ID Trader::GetLocation() const {
    return location;
}
vec<ID> & Trader::GetItinerary() {
    return itinerary;
}
void Trader::AddToItinerary(ID _id, int index) {
    vec<ID>::iterator it = itinerary.begin()+index;
    itinerary.insert(it,_id);
}