#include"trader.hpp"

Trader::Trader() {

}
Trader::Trader(ID _id, ID _location)
    : location(_location)
{}
ID Trader::GetID() const {
    return actor->GetID();
}
gcon::Actor * Trader::GetActor() {
    return actor;
}
void Trader::SetActor(gcon::Actor * _actor) {
    actor = _actor;
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