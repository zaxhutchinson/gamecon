#pragma once

#include"defs.hpp"
#include"gamecon.hpp"
#include"vec2.hpp"
#include"gtime.hpp"

using namespace gcon;

class Store {
private:
    Node * node;
    Time hour_open;
    Time hour_closed;
    Vec2 location;
public:
    Store();
    Store(Node * _node);
    Node * GetNode();
    bool IsOpen();
};