#include"store.hpp"

Store::Store() {
    hour_open = Time(-1,0,0);
    hour_closed = Time(-1,23,0);
    node = nullptr;
}
Store::Store(Node * _node) {
    hour_open = Time(-1,0,0);
    hour_closed = Time(-1,23,0);
    node = _node;
}
Node * Store::GetNode() {
    return node;
}