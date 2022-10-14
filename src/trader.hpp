#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"

class Trader {
private:
    ID id;
    ID location;
    gcon::Actor * actor;
    vec<ID> itinerary;
public:
    Trader();
    Trader(ID _id, ID _location);
    Trader(const Trader & t) = default;
    Trader(Trader && t) = default;
    Trader& operator=(const Trader & t) = default;
    Trader& operator=(Trader && t) = default;
    ID GetID() const;
    gcon::Actor * GetActor();
    void SetActor(gcon::Actor * _actor);
    ID GetLocation() const;
    vec<ID> & GetItinerary();
    void AddToItinerary(ID _id, int index);
};