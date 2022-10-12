#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"
#include"supdem.hpp"

class Business {
private:
    ID id;
    Vec2 location;
    vec<gcon::Item> stock;
    vec<Event> supply_events;
    vec<Event> demand_events;
public:
};