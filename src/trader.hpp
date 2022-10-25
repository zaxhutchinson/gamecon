#pragma once

#include<cmath>

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"
#include"gtime.hpp"

enum class TraderRtnType {
    UNCHANGED,
    DEPARTED,
    ARRIVED,
};

struct TraderRtn {
    TraderRtnType type;
    ID from;
    ID to;
};

class Trader {
private:
    ID id;
    ID location;
    gcon::Actor * actor;
    vec<ID> itinerary;
    double speed;
    bool random_itinerary;
    ID destination;
    Time last_update_time;
    Time time_at_destination;
    Time remaining_travel_time;
    Time remaining_destination_time;

public:
    Trader();
    Trader(ID _id, ID _location, double _speed, bool _random_itinerary, Time _time_at_dest);
    Trader(const Trader & t) = default;
    Trader(Trader && t) = default;
    Trader& operator=(const Trader & t) = default;
    Trader& operator=(Trader && t) = default;
    ID GetID() const;
    gcon::Actor * GetActor();
    double GetSpeed() const;
    bool HasRandomItinerary() const;
    ID GetDestination() const;
    void SetActor(gcon::Actor * _actor);
    ID GetLocation() const;
    vec<ID> & GetItinerary();
    ID GetNextDestination();
    ID GetRandomDestination(RNG * rng);
    void SetItinerary(vec<ID> _itinerary);
    void AddToItinerary(ID _id, int index);
    void SetDestination(ID _id);
    Time GetRemainingTravelTime() const;
    void SetTravelTime(double distance);
    TraderRtn Update(Time & curtime, RNG * rng);
};