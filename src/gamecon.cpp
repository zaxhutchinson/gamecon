#include"gamecon.hpp"

namespace gcon {

    /* Item Implementation */

    Item::Item() { amt = 0; }
    Item::Item(ID _id) { id = _id; amt = 0;}
    Item::Item(ID _id, i64 _amt) { id = _id; amt = _amt;}
    ID Item::GetID() const { return id; }
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
    Delivery::Delivery(Item _item, vec<ID> & _dest_list) {
        item = _item;
        dest_list = _dest_list;
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

    void Node::AddConn(ID _id) {
        if(!HasConn(_id) && _id != id) {
            conns.push_back(id);
        }
    }
    void Node::AddConns(vec<ID> & _conns) {
        for(
            vec<ID>::iterator it = _conns.begin();
            it != _conns.end();
            it++
        ) {
            AddConn(*it);
        }
    }
    bool Node::HasConn(ID _id) {
        return FindConn(_id) != conns.end();
    }
    vec<ID>::iterator Node::FindConn(ID _id) {
        for(
            vec<ID>::iterator it = conns.begin();
            it != conns.end();
            it++
        ) {
            if(*it==_id) return it;
        }
        return conns.end();
    }
    void Node::RemoveConn(ID _id) {
        vec<ID>::iterator it = FindConn(_id);
        if(it != conns.end()) conns.erase(it);
    }
    vec<ID> & Node::GetConns() {
        return conns;
    }
    void Node::ClearConns() {
        conns.clear();
    }
    bool Node::HasItem(ID item_id) {
        for(
            vec<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetID()) return true;
        }
        return false;
    }
    vec<Item>::iterator Node::FindItem(ID item_id) {
        for(
            vec<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetID()) return it;
        }
        return items.end();
    }
    void Node::AddItem(Item i) {
        vec<Item>::iterator it = FindItem(i.GetID());
        if(it!=items.end()) {
            it->SetAmt(it->GetAmt()+i.GetAmt());
        } else {
            items.push_back(i);
        }
    }
    void Node::RemoveItem(vec<Item>::iterator it) {
        items.erase(it);
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
                
            */
            vec<ID> & req_dest_list = it->GetDestList();

            // If the previous node was not next_dest, send request.
            if(req_dest_list.back()!=next_dest) {
                if(req_dest_list.front() != next_dest) {
                    Request r = *it;
                    r.PushDest(id);
                    reqs.push_back(r);
                    it = requests.erase(it);
                }
                it++;
            }
            // But if the previous node was next_dest, but this node
            // has only one connection, then send, unless the one connection
            // is back to the node that created the request
            else if(conns.size()==1) {
                if(req_dest_list.front() != next_dest) {
                    Request r = *it;
                    r.PushDest(id);
                    reqs.push_back(r);
                    it = requests.erase(it);
                }
                it++;
            }
            else {
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

    void Node::CheckAndFillRequests() {
        for(
            vec<Request>::iterator it = requests.begin();
            it != requests.end();
        ) {
            vec<Item>::iterator item_it = FindItem(it->GetItem().GetID());
            if(item_it != items.end()) {

                int amt_req = it->GetItem().GetAmt();
                int amt_has = item_it->GetAmt();

                if(amt_has >= amt_req) { // Has enough to satisfy req
                    item_it->SetAmt(amt_has-amt_req);
                    Item item(it->GetItem().GetID(), amt_req);
                    Delivery delivery(item, it->GetDestList());
                    deliveries.push_back(delivery);
                    it = requests.erase(it);
                } else { // Does not have enough
                    item_it->SetAmt(0);
                    Item item(it->GetItem().GetID(), amt_has);
                    Delivery delivery(item, it->GetDestList());
                    deliveries.push_back(delivery);
                    it->GetItem().SetAmt(amt_req-amt_has);
                    it++;
                }

                // The above transactions reduced the item count to 0.
                // Remove the item from the item list.
                if(item_it->GetAmt()==0) {
                    RemoveItem(item_it);
                }
            }
        }
    }




    Trader::Trader() {}
    Trader::Trader(ID _id) {
        id = _id;
    }
    Trader::Trader(ID _id, vec<ID> & _nodes) {
        id = _id;
        nodes = _nodes;
    }
    ID Trader::GetID() const {
        return id;
    }
    void Trader::AddNode(ID node) {
        if(!HasNode(node)) {
            nodes.push_back(node);
        }
    }
    bool Trader::HasNode(ID node) {
        for(
            vec<ID>::iterator it = nodes.begin();
            it != nodes.end();
            it++
        ) {
            if(*it==node) return true;
        }
        return false;
    }
    void Trader::RemoveNode(ID node) {
        for(
            vec<ID>::iterator it = nodes.begin();
            it != nodes.end();
        ) {
            if(*it==node) {
                it = nodes.erase(it);
            } else {
                it++;
            }
        }
    }
    vec<ID> & Trader::GetNodes() {
        return nodes;
    }
    vec<Request> & Trader::GetRequests() {
        return requests;
    }
    vec<Delivery> & Trader::GetDeliveries() {
        return deliveries;
    }
    void Trader::AddRequest(Request r) {
        requests.push_back(r);
    }
    void Trader::AddDelivery(Delivery d) {
        deliveries.push_back(d);
    }
    void Trader::AddRequests(vec<Request> & reqs) {
        for(
            vec<Request>::iterator it = reqs.begin();
            it != reqs.end(); it++
        ) {
            requests.push_back(*it);
        }
    }
    void Trader::AddDeliveries(vec<Delivery> & dels) {
        for(
            vec<Delivery>::iterator it = dels.begin();
            it != dels.end(); it++
        ) {
            deliveries.push_back(*it);
        }
    }
    // vec<Request>::iterator Agent::RemoveRequest(vec<Request>::iterator it) {
    //     return requests.erase(it);
    // }
    // vec<Delivery>::iterator Agent::RemoveDelivery(vec<Delivery>::iterator it) {
    //     return deliveries.erase(it);
    // }






    TradeNetwork::TradeNetwork() {}

    void TradeNetwork::RefreshNetwork() {
        for(
            umap<ID,Node>::iterator it = nodes.begin();
            it != nodes.end();
            it++ 
        ) {
            it->second.ClearConns();
        }

        for(
            umap<ID,Trader>::iterator it = traders.begin();
            it != traders.end();
            it++
        ) {
            vec<ID> conns = it->second.GetNodes();
            for(
                vec<ID>::iterator conn_it = conns.begin();
                conn_it != conns.end();
                conn_it++
            ) {
                Node * n = GetNode(*conn_it);
                n->AddConns(conns);
            }
        }
    }

    void TradeNetwork::RegisterNode(Node node) {
        nodes.emplace(node.GetID(),node);
    }
    void TradeNetwork::RegisterTrader(Trader trader) {
        traders.emplace(trader.GetID(), trader);
    }
    Node * TradeNetwork::GetNode(ID node_id) {
        try {
            return &(nodes.at(node_id));
        } catch(std::out_of_range & e) {
            return nullptr;
        }
    }
    Trader * TradeNetwork::GetTrader(ID trader_id) {
        try {
            return &(traders.at(trader_id));
        } catch(std::out_of_range & e) {
            return nullptr;
        }
    }
    void TradeNetwork::TraderArrives(ID trader_id, ID from_node_id, ID to_node_id) {
        Node * from_node = GetNode(from_node_id);
        Node * to_node = GetNode(to_node_id);
        Trader * trader = GetTrader(trader_id);
        if(!to_node || !from_node || !trader) return;

        vec<Delivery> & inbound_deliveries = trader->GetDeliveries();
        vec<Request> & inbound_requests = trader->GetRequests();

        // Try to add all of the trader's requests to this node.
        for(
            vec<Request>::iterator it = inbound_requests.begin();
            it != inbound_requests.end();
        ) {
            if(to_node->AddRequest(*it)) {
                it = inbound_requests.erase(it);
            } else {
                it++;
            }
        }

        // Try to add all of the trader's deliveries to this node.
        for(
            vec<Delivery>::iterator it = inbound_deliveries.begin();
            it != inbound_deliveries.end();
        ) {
            if(to_node->AddDelivery(*it)) {
                it = inbound_deliveries.erase(it);
            } else {
                it++;
            }
        }
    }
    void TradeNetwork::TraderLeaves(ID trader_id, ID from_node_id, ID to_node_id) {
        Node * from_node = GetNode(from_node_id);
        Node * to_node = GetNode(to_node_id);
        Trader * trader = GetTrader(trader_id);
        if(!to_node || !from_node || !trader) return;

        vec<Delivery> outbound_deliveries = from_node->PassOnDeliveries(to_node_id);
        vec<Request> outbound_requests = from_node->PassOnRequests(to_node_id);

        trader->AddDeliveries(outbound_deliveries);
        trader->AddRequests(outbound_requests);
    }
}