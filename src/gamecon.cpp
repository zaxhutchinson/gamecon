#include"gamecon.hpp"

namespace gcon {

    /* Item Implementation */

    Item::Item() { amt = 0; }
    Item::Item(ID _id) { id = _id; amt = 0;}
    Item::Item(ID _id, int64_t _amt) { id = _id; amt = _amt;}
    std::string Item::ToString() {
        std::stringstream ss;
        ss << "ITEM " << id << " " << amt;
        return ss.str();
    }
    ID Item::GetID() const { return id; }
    int64_t Item::GetAmt() const { return amt; }
    void Item::SetAmt(int64_t a) { amt = a; }

    /* Request Implementation */
    Request::Request() { }
    Request::Request(Item _item) {
        item = _item;
    }
    Request::Request(Item _item, ID _dest) {
        item = _item;
        dest_list.push_back(_dest);
    }
    std::string Request::ToString() {
        std::stringstream ss;
        ss << "REQUEST " << item.ToString() << " Dests: ";
        for(size_t i = 0; i < dest_list.size(); i++) {
            ss << dest_list[i] << " ";
        }
        return ss.str();
    }
    Item& Request::GetItem() { return item; }
    std::vector<ID>& Request::GetDestList() { return dest_list; }
    bool Request::IsIDInDestList(ID id) {
        for(
            std::vector<ID>::iterator it = dest_list.begin();
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
    std::optional<ID> Request::PopDest() {
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
    Delivery::Delivery(Item _item, std::vector<ID> & _dest_list) {
        item = _item;
        dest_list = _dest_list;
    }
    std::string Delivery::ToString() {
        std::stringstream ss;
        ss << "DELIVERY " << item.ToString() << " Dests: ";
        for(size_t i = 0; i < dest_list.size(); i++) {
            ss << dest_list[i] << " ";
        }
        return ss.str();
    }
    Item& Delivery::GetItem() { return item; }
    std::vector<ID>& Delivery::GetDestList() { return dest_list; }
    bool Delivery::IsIDInDestList(ID id) {
        for(
            std::vector<ID>::iterator it = dest_list.begin();
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

    std::string Node::ToString() {
        std::stringstream ss;
        ss << "NODE " << id << "\n   CONNS ";
        for(size_t i = 0; i < conns.size(); i++) {
            ss << conns[i] << " ";
        }
        for(size_t i = 0; i < items.size(); i++) {
            ss << "\n   " << items[i].ToString();
        }
        for(size_t i = 0; i < requests.size(); i++) {
            ss << "\n   " << requests[i].ToString();
        }
        for(size_t i = 0; i < deliveries.size(); i++) {
            ss << "\n   " << deliveries[i].ToString();
        }
        return ss.str();
    }

    ID Node::GetID() const { return id; }

    void Node::AddConn(ID _id) {
        if(!HasConn(_id) && _id != id) {
            conns.push_back(_id);
        }
    }
    void Node::AddConns(std::vector<ID> & _conns) {
        for(
            std::vector<ID>::iterator it = _conns.begin();
            it != _conns.end();
            it++
        ) {
            AddConn(*it);
        }
    }
    bool Node::HasConn(ID _id) {
        return FindConn(_id) != conns.end();
    }
    std::vector<ID>::iterator Node::FindConn(ID _id) {
        for(
            std::vector<ID>::iterator it = conns.begin();
            it != conns.end();
            it++
        ) {
            if(*it==_id) return it;
        }
        return conns.end();
    }
    void Node::RemoveConn(ID _id) {
        std::vector<ID>::iterator it = FindConn(_id);
        if(it != conns.end()) conns.erase(it);
    }
    std::vector<ID> & Node::GetConns() {
        return conns;
    }
    void Node::ClearConns() {
        conns.clear();
    }
    bool Node::HasItem(ID item_id) {
        for(
            std::vector<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetID()) return true;
        }
        return false;
    }
    std::vector<Item>::iterator Node::FindItem(ID item_id) {
        for(
            std::vector<Item>::iterator it = items.begin();
            it != items.end();
            it++
        ) {
            if(item_id==it->GetID()) return it;
        }
        return items.end();
    }
    void Node::AddItem(Item i) {
        std::vector<Item>::iterator it = FindItem(i.GetID());
        if(it!=items.end()) {
            it->SetAmt(it->GetAmt()+i.GetAmt());
        } else {
            items.push_back(i);
        }
    }
    void Node::RemoveItem(std::vector<Item>::iterator it) {
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
            std::vector<ID>::reverse_iterator rit = d.GetDestList().rbegin();
            rit != d.GetDestList().rend();
        ) {
            // Deleting with reverse_iterators is bit shit.
            if((*rit)!=id) {
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

    void Node::InitiateRequest(Item item) {
        Request r(item);
        requests.push_back(r);
    }

    std::vector<Request> Node::PassOnRequests(ID next_dest) {
        std::vector<Request> reqs;
        for(
            std::vector<Request>::iterator it = requests.begin();
            it != requests.end();
        ) {
            /* 
                Look for the next_dest in this request's dest_list.
                
            */
            std::vector<ID> & req_dest_list = it->GetDestList();

            if(req_dest_list.size()==0) {
                Request r = *it;
                r.PushDest(id);
                reqs.push_back(r);
                it = requests.erase(it);
            } else {
                if(conns.size()==1) {
                    Request r = *it;
                    r.PushDest(id);
                    reqs.push_back(r);
                    it = requests.erase(it);
                }
                else if(req_dest_list.back() == next_dest && req_dest_list.front() != next_dest) {
                    Request r = *it;
                    r.PushDest(id);
                    reqs.push_back(r);
                    it = requests.erase(it);
                }
                else if(req_dest_list.back() != next_dest && req_dest_list.front() != next_dest) {
                    Request r = *it;
                    r.PushDest(id);
                    reqs.push_back(r);
                    it = requests.erase(it);
                } else {
                    it++;
                }
            }
        }

        return reqs;
    }

    std::vector<Delivery> Node::PassOnDeliveries(ID next_dest) {

        std::vector<Delivery> dels;

        /*
            If the next destination of the visiting agent, is in the delivery's
            destination list, give this delivery to the agent.
        */
        for(
            std::vector<Delivery>::iterator it = deliveries.begin();
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
            std::vector<Request>::iterator it = requests.begin();
            it != requests.end();
        ) {
            std::vector<Item>::iterator item_it = FindItem(it->GetItem().GetID());
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
            } else {
                it++;
            }
        }
    }




    Actor::Actor() {}
    Actor::Actor(ID _id) {
        id = _id;
    }
    Actor::Actor(ID _id, std::vector<ID> & _nodes) {
        id = _id;
        nodes = _nodes;
    }
    std::string Actor::ToString() {
        std::stringstream ss;
        ss << "TRADER " << id << "\n   NODES ";
        for(size_t i = 0; i < nodes.size(); i++) {
            ss << nodes[i] << " ";
        }
        for(size_t i = 0; i < requests.size(); i++) {
            ss << "\n   " << requests[i].ToString();
        }
        for(size_t i = 0; i < deliveries.size(); i++) {
            ss << "\n   " << deliveries[i].ToString();
        }
        return ss.str();
    }
    ID Actor::GetID() const {
        return id;
    }
    void Actor::AddNode(ID node) {
        if(!HasNode(node)) {
            nodes.push_back(node);
        }
    }
    bool Actor::HasNode(ID node) {
        for(
            std::vector<ID>::iterator it = nodes.begin();
            it != nodes.end();
            it++
        ) {
            if(*it==node) return true;
        }
        return false;
    }
    void Actor::RemoveNode(ID node) {
        for(
            std::vector<ID>::iterator it = nodes.begin();
            it != nodes.end();
        ) {
            if(*it==node) {
                it = nodes.erase(it);
            } else {
                it++;
            }
        }
    }
    std::vector<ID> & Actor::GetNodes() {
        return nodes;
    }
    std::vector<Request> & Actor::GetRequests() {
        return requests;
    }
    std::vector<Delivery> & Actor::GetDeliveries() {
        return deliveries;
    }
    void Actor::AddRequest(Request r) {
        requests.push_back(r);
    }
    void Actor::AddDelivery(Delivery d) {
        deliveries.push_back(d);
    }
    void Actor::AddRequests(std::vector<Request> & reqs) {
        for(
            std::vector<Request>::iterator it = reqs.begin();
            it != reqs.end(); it++
        ) {
            requests.push_back(*it);
        }
    }
    void Actor::AddDeliveries(std::vector<Delivery> & dels) {
        for(
            std::vector<Delivery>::iterator it = dels.begin();
            it != dels.end(); it++
        ) {
            deliveries.push_back(*it);
        }
    }
    // std::vector<Request>::iterator Agent::RemoveRequest(std::vector<Request>::iterator it) {
    //     return requests.erase(it);
    // }
    // std::vector<Delivery>::iterator Agent::RemoveDelivery(std::vector<Delivery>::iterator it) {
    //     return deliveries.erase(it);
    // }






    Network::Network() {}

    std::string Network::ToString() {
        std::stringstream ss;
        for(
            std::unordered_map<ID,std::unique_ptr<Node>>::iterator it = nodes.begin();
            it != nodes.end(); it++
        ) {
            ss << it->second->ToString() << "\n\n";
        }

        for(
            std::unordered_map<ID,std::unique_ptr<Actor>>::iterator it = actors.begin();
            it != actors.end(); it++
        ) {
            ss << it->second->ToString() << "\n\n";
        }
        return ss.str();
    }

    void Network::RefreshNetwork() {
        for(
            std::unordered_map<ID,std::unique_ptr<Node>>::iterator it = nodes.begin();
            it != nodes.end();
            it++ 
        ) {
            it->second->ClearConns();
        }

        for(
            std::unordered_map<ID,std::unique_ptr<Actor>>::iterator it = actors.begin();
            it != actors.end();
            it++
        ) {
            std::vector<ID> conns = it->second->GetNodes();
            for(
                std::vector<ID>::iterator conn_it = conns.begin();
                conn_it != conns.end();
                conn_it++
            ) {
                Node * n = GetNode(*conn_it);
                n->AddConns(conns);
            }
        }
    }

    void Network::RegisterNode(std::unique_ptr<Node> node) {
        nodes.emplace(node->GetID(),std::move(node));
    }
    void Network::RegisterActor(std::unique_ptr<Actor> actor) {
        actors.emplace(actor->GetID(), std::move(actor));
    }
    Node * Network::GetNode(ID node_id) {
        try {
            return nodes.at(node_id).get();
        } catch(std::out_of_range & e) {
            return nullptr;
        }
    }
    Actor * Network::GetActor(ID actor_id) {
        try {
            return actors.at(actor_id).get();
        } catch(std::out_of_range & e) {
            return nullptr;
        }
    }
    void Network::ActorArrives(ID actor_id, ID from_node_id, ID to_node_id) {
        Node * from_node = GetNode(from_node_id);
        Node * to_node = GetNode(to_node_id);
        Actor * actor = GetActor(actor_id);
        if(!to_node || !from_node || !actor) return;

        std::vector<Delivery> & inbound_deliveries = actor->GetDeliveries();
        std::vector<Request> & inbound_requests = actor->GetRequests();

        // Try to add all of the actor's requests to this node.
        for(
            std::vector<Request>::iterator it = inbound_requests.begin();
            it != inbound_requests.end();
        ) {
            if(to_node->AddRequest(*it)) {
                it = inbound_requests.erase(it);
            } else {
                it++;
            }
        }

        // Try to add all of the actor's deliveries to this node.
        for(
            std::vector<Delivery>::iterator it = inbound_deliveries.begin();
            it != inbound_deliveries.end();
        ) {
            if(to_node->AddDelivery(*it)) {
                it = inbound_deliveries.erase(it);
            } else {
                it++;
            }
        }

        to_node->CheckAndFillRequests();
    }
    void Network::ActorLeaves(ID actor_id, ID from_node_id, ID to_node_id) {
        Node * from_node = GetNode(from_node_id);
        Node * to_node = GetNode(to_node_id);
        Actor * actor = GetActor(actor_id);
        if(!to_node || !from_node || !actor) return;

        to_node->CheckAndFillRequests();

        std::vector<Delivery> outbound_deliveries = from_node->PassOnDeliveries(to_node_id);
        std::vector<Request> outbound_requests = from_node->PassOnRequests(to_node_id);

        actor->AddDeliveries(outbound_deliveries);
        actor->AddRequests(outbound_requests);
    }
}