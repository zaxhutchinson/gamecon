#include<string>
#include<memory>
#include<cstdint>
#include<mutex>
#include<vector>
#include<optional>
#include<unordered_map>
#include<sstream>
#include<iostream>

namespace gcon {

    using ID = std::string;

    /* Item  */
    class Item {
    private:
        ID id;
        int64_t amt;
    public:
        Item();
        Item(ID _id);
        Item(ID _id, int64_t _amt);
        Item(const Item & i) = default;
        Item(Item && i) = default;
        Item& operator=(const Item & i) = default;
        Item& operator=(Item && i) = default;
        std::string ToString();
        ID GetID() const;
        int64_t GetAmt() const;
        void SetAmt(int64_t a);
    };

    /* Request */
    class Request {
    private:
        Item item;
        std::vector<ID> dest_list;
    public:
        Request();
        Request(Item _item);
        Request(Item _item, ID _dest);
        Request(const Request & r) = default;
        Request(Request && r) = default;
        Request& operator=(const Request & r) = default;
        Request& operator=(Request && r) = default;
        std::string ToString();
        Item& GetItem();
        std::vector<ID>& GetDestList();
        bool IsIDInDestList(ID id);
        void PushDest(ID new_dest);
        std::optional<ID> PopDest();
    };

    /* Delivery */
    class Delivery {
    private:
        Item item;
        std::vector<ID> dest_list;
    public:
        Delivery();
        Delivery(Item _item, ID _dest);
        Delivery(Item _item, std::vector<ID> & _dest_list);
        Delivery(const Delivery & r) = default;
        Delivery(Delivery && r) = default;
        Delivery& operator=(const Delivery & r) = default;
        Delivery& operator=(Delivery && r) = default;
        std::string ToString();
        Item& GetItem();
        std::vector<ID>& GetDestList();
        bool IsIDInDestList(ID id);
    };


    class Node {
    private:
        ID id;
        std::vector<ID> conns;
        std::vector<Item> items;
        std::vector<Request> requests;
        std::vector<Delivery> deliveries;
    public:
        Node();
        Node(ID _id);
        Node(const Node & n) = default;
        Node(Node && n) = default;
        Node& operator=(const Node & n) = default;
        Node& operator=(Node && n) = default;
        std::string ToString();
        ID GetID() const;
        void AddConn(ID _id);
        void AddConns(std::vector<ID> & _conns);
        bool HasConn(ID _id);
        std::vector<ID>::iterator FindConn(ID _id);
        void RemoveConn(ID _id);
        std::vector<ID> & GetConns();
        void ClearConns();
        bool HasItem(ID item_id);
        std::vector<Item>::iterator FindItem(ID item_id);
        void AddItem(Item i);
        void RemoveItem(std::vector<Item>::iterator it);
        bool AddDelivery(Delivery d);
        bool AddRequest(Request r);
        void InitiateRequest(Item item);
        std::vector<Request> PassOnRequests(ID next_dest);
        std::vector<Delivery> PassOnDeliveries(ID next_dest);
        void CheckAndFillRequests();
        
    };


    /* Trader class */
    class Actor {
    private:
        ID id;
        std::vector<ID> nodes;
        std::vector<Request> requests;
        std::vector<Delivery> deliveries;
    public:
        Actor();
        Actor(ID _id);
        Actor(ID _id, std::vector<ID> & _nodes);
        Actor(const Actor & a) = default;
        Actor(Actor && a) = default;
        Actor& operator=(const Actor & a) = default;
        Actor& operator=(Actor && a) = default;
        std::string ToString();
        ID GetID() const;
        void AddNode(ID node);
        bool HasNode(ID node);
        void RemoveNode(ID node);
        std::vector<ID> & GetNodes();
        std::vector<Request> & GetRequests();
        std::vector<Delivery> & GetDeliveries();
        void AddRequest(Request r);
        void AddDelivery(Delivery d);
        void AddRequests(std::vector<Request> & reqs);
        void AddDeliveries(std::vector<Delivery> & dels);
        // std::vector<Request>::iterator RemoveRequest(std::vector<Request>::iterator it);
        // std::vector<Delivery>::iterator RemoveDelivery(std::vector<Delivery>::iterator it);

    };


    class Network {
    private:
        std::unordered_map<ID,Node> nodes;
        std::unordered_map<ID,Actor> actors;
    public:
        Network();
        Network(const Network & tn) = delete;
        Network(Network && tn) = delete;
        Network& operator=(const Network & tn) = delete;
        Network& operator=(Network && tn) = delete;
        std::string ToString();
        /* RefreshNetwork
            This function removes all connections from the nodes and
            uses the traders to re-add all connections to the nodes.
            This should be called whenever a trader dies, removes a
            node from the trader's network, etc.
        */
        void RefreshNetwork();
        void RegisterNode(Node node);
        void RegisterActor(Actor actor);
        Node * GetNode(ID node_id);
        Actor * GetActor(ID actor_id);
        void ActorArrives(ID actor_id, ID from_node_id, ID to_node_id);
        void ActorLeaves(ID actor_id, ID from_node_id, ID to_node_id);
    };


}