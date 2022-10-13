#pragma once

/* Supply and Demand */

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"
#include"gtime.hpp"


class Event {
protected:
    gcon::Item item;
    double probability;
    Time last_event;
    Time freqency;
public:
    Event();
    Event(gcon::Item _item, double _prob, Time _freq);
    Event(const Event & s) = default;
    Event(Event && s) = default;
    Event& operator=(const Event & s) = default;
    Event& operator=(Event && s) = default;
    gcon::Item GetItem() const;
    double GetProbability() const;
    Time GetFrequency() const;

    opt<gcon::Item> Check(RNG * rng, Time & curtime);
};