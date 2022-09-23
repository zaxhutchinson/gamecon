#include"gamecon.hpp"

namespace gcon {

    /* Item Implementation */

    Item::Item() { amt = 0; }
    Item::Item(ID _type) { type = _type; amt = 0;}
    Item::Item(ID _type, i64 _amt) { type = _type; amt = _amt;}
    Item::Item(const Request & r) {
        type = r.GetType();
        amt = r.GetAmt();
    }
    ID Item::GetType() const { return type; }
    i64 Item::GetAmt() const { return amt; }
    void Item::SetAmt(i64 a) { amt = a; }




    /* Request Implementation */
    Request::Request() { amt = 0; }
    Request::Request(ID _type) { type = _type; amt = 0; }
    Request::Request(ID _type, i64 _amt) { type = _type; amt = _amt; }
    Request::Request(const Item & i) {
        type = i.GetType();
        amt = i.GetAmt();
    }
    ID Request::GetType() const { return type; }
    i64 Request::GetAmt() const { return amt; }



    /* Node Implementation */
    Node::Node() {}
    Node::Node(ID _id) { id = _id; }
    ID Node::GetID() const { return id; }
    void Node::AddItem(Item i) {

    }
}