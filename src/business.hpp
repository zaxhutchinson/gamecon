#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"
#include"event.hpp"

class Business {
private:
    ID id;
    Vec2 location;
    gcon::Node * node;
    vec<Event> supply_events;
    vec<Event> demand_events;
public:
    Business();
    Business(ID _id, Vec2 _location);
    Business(const Business & b) = default;
    Business(Business && b) = default;
    Business& operator=(const Business & b) = default;
    Business& operator=(Business && b) = default;
    ID GetID() const;
    Vec2 GetLocation() const;
    gcon::Node * GetNode();
    void SetNode(gcon::Node * _node);
    void AddStock(gcon::Item item);
    void AddRequest(gcon::Item item);
    void AddSupplyEvent(Event event);
    void AddDemandEvent(Event event);

    void CheckEvents(RNG * rng, Time & curtime);

};