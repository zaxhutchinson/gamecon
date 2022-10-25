#include"trader.hpp"

Trader::Trader() {

}
Trader::Trader(ID _id, ID _location, double _speed, bool _random_itinerary, Time _time_at_dest)
    : id(_id), location(_location), speed(_speed), random_itinerary(_random_itinerary), destination(_location), time_at_destination(_time_at_dest)
{}
ID Trader::GetID() const {
    return id;
}
gcon::Actor * Trader::GetActor() {
    return actor;
}
double Trader::GetSpeed() const {
    return speed;
}
bool Trader::HasRandomItinerary() const {
    return random_itinerary;
}
ID Trader::GetDestination() const {
    return destination;
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
ID Trader::GetNextDestination() {
    for(sizet i = 0; i < itinerary.size(); i++) {
        if(itinerary[i]==location) {
            return itinerary[(i+1)%itinerary.size()];
        }
    }
    return itinerary[0];
}
ID Trader::GetRandomDestination(RNG * rng) {
    std::uniform_int_distribution<int> dist(0,itinerary.size()-1);
    return itinerary[dist(*rng)];
}
void Trader::SetItinerary(vec<ID> _itinerary) {
    itinerary = _itinerary;
}
void Trader::AddToItinerary(ID _id, int index) {
    vec<ID>::iterator it = itinerary.begin()+index;
    itinerary.insert(it,_id);
}
void Trader::SetDestination(ID _id) {
    destination = _id;
}
Time Trader::GetRemainingTravelTime() const {
    return remaining_travel_time;
}
void Trader::SetTravelTime(double distance) {
    int quarters = static_cast<int>(std::ceil(distance / speed));
    remaining_travel_time = Time(0,0,quarters);
}
TraderRtn Trader::Update(Time & curtime, RNG * rng) {

    TraderRtn rtn = {TraderRtnType::UNCHANGED,ID(),ID()};

    Time time_since_last_update = curtime - last_update_time;

    // If the trader is travelling update their travel time
    // and if they have no travel time remaining set their
    // location to their destination.
    if(destination != location) {
        remaining_travel_time -= time_since_last_update;
        
        if(remaining_travel_time <= Time()) {
            remaining_travel_time = Time();

            rtn = {TraderRtnType::ARRIVED, location, destination};

            location = destination;
            remaining_destination_time = time_at_destination;
        }
    } else {
        remaining_destination_time -= time_since_last_update;
        if(remaining_destination_time <= Time()) {
            remaining_destination_time = Time();
            if(HasRandomItinerary()) {
                destination = GetRandomDestination(rng);
            } else {
                destination = GetNextDestination();
            }
            rtn = {TraderRtnType::DEPARTED, location, destination};
        }
    }

    last_update_time = curtime;

    return rtn;

}
