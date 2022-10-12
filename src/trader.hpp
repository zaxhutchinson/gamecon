#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"

class Trader {
private:
    Vec2 location;
    gcon::Actor * actor;
    vec<ID> stores;
public:
    Trader();
    Trader(Vec2 _location, gcon::Actor * _actor);
    Trader(const Trader & t) = default;
    Trader(Trader && t) = default;
    Trader& operator=(const Trader & t) = default;
    Trader& operator=(Trader && t) = default;
    ID GetID() const;
    gcon::Actor * GetActor();
    Vec2 GetLocation() const;
    vec<ID> & GetStores();
    void AddStore(ID s);
};