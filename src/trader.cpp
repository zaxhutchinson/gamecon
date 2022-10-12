#include"trader.hpp"

Trader::Trader() {

}
Trader::Trader(Vec2 _location, gcon::Actor * _actor)
    : location(_location), actor(_actor)
{}
ID Trader::GetID() const {
    return actor->GetID();
}
gcon::Actor * Trader::GetActor() {
    return actor;
}
Vec2 Trader::GetLocation() const {
    return location;
}
vec<ID> & Trader::GetStores() {
    return stores;
}
void Trader::AddStore(ID s) {
    stores.push_back(s);
}