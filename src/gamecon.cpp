#include"gamecon.hpp"

namespace gcon {

    /* Item Implementation */

    Item::Item() { amt = 0; }
    Item::Item(ID _type) { type = _type; amt = 0;}
    Item::Item(ID _type, i64 _amt) { type = _type; amt = _amt;}
    ID Item::GetType() const { return type; }
    i64 Item::GetAmt() const { return amt; }
    void Item::SetAmt(i64 a) { amt = a; }

    /* Request Implementation */
    Request::Request() { }
    Request::Request(Item _item, ID _dest) {
        item = _item;
        dest_list.push_back(_dest);
    }
    Item& Request::GetItem() { return item; }
    vec<ID>& Request::GetDestList() { return dest_list; }
    bool Request::IsIDInDestList(ID id) {
        for(
            vec<ID>::iterator it = dest_list.begin();
            it != dest_list.end();
            it++
        ) {
            if(id==*it) return true;
        }
        return false;
    }
    void Request::PushDest(ID new_dest) {
        dest_list.push_back(new_dest);
    }
    opt<ID> Request::PopDest() {
        if(dest_list.size() > 0) {
            ID id = dest_list.back();
            dest_list.pop_back();
            return { id };
        } else {
            return std::nullopt;
        }
    }


    /* Delivery Implementation */
    Delivery::Delivery() { }
    Delivery::Delivery(Item _item, ID _dest) {
        item = _item;
        dest_list.push_back(_dest);
    }
    Item& Delivery::GetItem() { return item; }
    vec<ID>& Delivery::GetDestList() { return dest_list; }
    bool Delivery::IsIDInDestList(ID id) {
        for(
            vec<ID>::iterator it = dest_list.begin();
            it != dest_list.end();
            it++
        ) {
            if(*it==id) return true;
        }
        return false;
    }


    /* Node Implementation */
    Node::Node() {}
    Node::Node(ID _id) { id = _id; }
    ID Node::GetID() const { return id; }
    bool Node::HasItem(ID item_id) {
        for(
            vec<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetType()) return true;
        }
        return false;
    }
    vec<Item>::iterator Node::FindItem(ID item_id) {
        for(
            vec<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetType()) return it;
        }
        return items.end();
    }
    void Node::AddItem(Item i) {
        vec<Item>::iterator it = FindItem(i.GetType());
        if(it!=items.end()) {
            it->SetAmt(it->GetAmt()+i.GetAmt());
        } else {
            items.push_back(i);
        }
    }
    bool Node::AddDelivery(Delivery d) {
        // Trying to add a delivery to this node which is not in
        // its dest list.
        if(!d.IsIDInDestList(id)) return false;
        
        /* 
            Work backwards through the dest list removing this node's
            id and all ids after it. This allows for a delivery to
            find shortcuts back to its source.
        */
        for(
            vec<ID>::reverse_iterator rit = d.GetDestList().rbegin();
            rit != d.GetDestList().rbegin();
        ) {
            // Deleting with reverse_iterators is bit shit.
            if(*rit!=id) {
                std::advance(rit,1);
                d.GetDestList().erase(rit.base());
            } else {
                d.GetDestList().erase(std::next(rit).base());
                break;
            }
        }

        // If this node was the original destination, add item to items.
        if(d.GetDestList().size()==0) {
            AddItem(d.GetItem());
        } else {
            deliveries.push_back(d);
        }
        return true;
    }

    bool Node::AddRequest(Request r) {
        /*
            Add the request to the node so long as the node's id isn't
            already in the request's dest list. We don't add this node's
            id to the request's dest list until this request is passed
            on to someone else.
        */
        if(r.IsIDInDestList(id)) {
            return false;
        }
        else {
            requests.push_back(r);
            return true;
        }
    }

    vec<Request> Node::PassOnRequests(ID next_dest) {
        vec<Request> reqs;
        for(
            vec<Request>::iterator it = requests.begin();
            it != requests.end();
        ) {
            /* 
                Look for the next_dest in this request's dest_list.
                If this request has already been through the next dest of
                this agent, don't pass it on. No cycles. 
                Otherwise, remove from our dest list and pass it on.
            */

            if(!it->IsIDInDestList(next_dest)) {
                Request r = *it;
                r.PushDest(id);
                reqs.push_back(r);
                it = requests.erase(it);
            } else {
                it++;
            }
        }

        return reqs;
    }

    vec<Delivery> Node::PassOnDeliveries(ID next_dest) {

        vec<Delivery> dels;

        /*
            If the next destination of the visiting agent, is in the delivery's
            destination list, give this delivery to the agent.
        */
        for(
            vec<Delivery>::iterator it = deliveries.begin();
            it != deliveries.end();
        ) {
            if(it->IsIDInDestList(next_dest)) {
                dels.push_back(*it);
                it = deliveries.erase(it);
            } else {
                it++;
            }
        }

        return dels;

    }
}