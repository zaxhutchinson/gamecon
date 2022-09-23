#include<string>
#include<memory>
#include<cstdint>
#include<mutex>
#include<vector>
#include<optional>
#include<unordered_map>

namespace gcon {

    /* Aliases */
    template<typename T>
    using opt = std::optional<T>;
    using str = std::string;
    template<typename T>
    using sptr = std::shared_ptr<T>;
    using i64 = int64_t;
    template<typename T>
    using vec = std::vector<T>;
    using ID = i64;  // Override to use a different type
    template<typename T, typename U>
    using umap = std::unordered_map<T,U>;

    /* Item  */
    class Item {
    private:
        ID id;
        i64 amt;
    public:
        Item();
        Item(ID _id);
        Item(ID _id, i64 _amt);
        Item(const Item & i) = default;
        Item(Item && i) = default;
        Item& operator=(const Item & i) = default;
        Item& operator=(Item && i) = default;

        ID GetID() const;
        i64 GetAmt() const;
        void SetAmt(i64 a);
    };

    /* Request */

    class Request {
    private:
        Item item;
        vec<ID> dest_list;
    public:
        Request();
        Request(Item _item, ID _dest);
        Request(const Request & r) = default;
        Request(Request && r) = default;
        Request& operator=(const Request & r) = default;
        Request& operator=(Request && r) = default;
        Item& GetItem();
        vec<ID>& GetDestList();
        bool IsIDInDestList(ID id);
        void PushDest(ID new_dest);
        opt<ID> PopDest();
    };


    /* Delivery */
    class Delivery {
    private:
        Item item;
        vec<ID> dest_list;
    public:
        Delivery();
        Delivery(Item _item, ID _dest);
        Delivery(Item _item, vec<ID> & _dest_list);
        Delivery(const Delivery & r) = default;
        Delivery(Delivery && r) = default;
        Delivery& operator=(const Delivery & r) = default;
        Delivery& operator=(Delivery && r) = default;
        Item& GetItem();
        vec<ID>& GetDestList();
        bool IsIDInDestList(ID id);
    };


    class Node {
    private:
        ID id;
        vec<ID> conns;
        vec<Item> items;
        vec<Request> requests;
        vec<Delivery> deliveries;
    public:
        Node();
        Node(ID _id);
        Node(const Node & n) = default;
        Node(Node && n) = default;
        Node& operator=(const Node & n) = default;
        Node& operator=(Node && n) = default;
        ID GetID() const;
        void AddConn(ID _id);
        void AddConns(vec<ID> & _conns);
        bool HasConn(ID _id);
        vec<ID>::iterator FindConn(ID _id);
        void RemoveConn(ID _id);
        vec<ID> & GetConns();
        void ClearConns();
        bool HasItem(ID item_id);
        vec<Item>::iterator FindItem(ID item_id);
        void AddItem(Item i);
        void RemoveItem(vec<Item>::iterator it);
        bool AddDelivery(Delivery d);
        bool AddRequest(Request r);

        vec<Request> PassOnRequests(ID next_dest);
        vec<Delivery> PassOnDeliveries(ID next_dest);
        void CheckAndFillRequests();
        
    };


    /* Trader class */
    class Trader {
    private:
        ID id;
        vec<ID> nodes;
        vec<Request> requests;
        vec<Delivery> deliveries;
    public:
        Trader();
        Trader(ID _id);
        Trader(ID _id, vec<ID> & _nodes);
        Trader(const Trader & a) = default;
        Trader(Trader && a) = default;
        Trader& operator=(const Trader & a) = default;
        Trader& operator=(Trader && a) = default;
        ID GetID() const;
        void AddNode(ID node);
        bool HasNode(ID node);
        void RemoveNode(ID node);
        vec<ID> & GetNodes();
        vec<Request> & GetRequests();
        vec<Delivery> & GetDeliveries();
        void AddRequest(Request r);
        void AddDelivery(Delivery d);
        void AddRequests(vec<Request> & reqs);
        void AddDeliveries(vec<Delivery> & dels);
        // vec<Request>::iterator RemoveRequest(vec<Request>::iterator it);
        // vec<Delivery>::iterator RemoveDelivery(vec<Delivery>::iterator it);

    };


    class TradeNetwork {
    private:
        umap<ID,Node> nodes;
        umap<ID,Trader> traders;
    public:
        TradeNetwork();
        TradeNetwork(const TradeNetwork & tn) = delete;
        TradeNetwork(TradeNetwork && tn) = delete;
        TradeNetwork& operator=(const TradeNetwork & tn) = delete;
        TradeNetwork& operator=(TradeNetwork && tn) = delete;
        /* RefreshNetwork
            This function removes all connections from the nodes and
            uses the traders to re-add all connections to the nodes.
            This should be called whenever a trader dies, removes a
            node from the trader's network, etc.
        */
        void RefreshNetwork();
        void RegisterNode(Node node);
        void RegisterTrader(Trader trader);
        Node * GetNode(ID node_id);
        Trader * GetTrader(ID trader_id);
        void TraderArrives(ID trader_id, ID from_node_id, ID to_node_id);
        void TraderLeaves(ID trader_id, ID from_node_id, ID to_node_id);
    };


}