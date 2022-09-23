#include<string>
#include<memory>
#include<cstdint>
#include<mutex>
#include<vector>
#include<optional>

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
    

    /* Forwards */
    class Request;

    /* Item  */
    class Item {
    private:
        ID type;
        i64 amt;
    public:
        Item();
        Item(ID _type);
        Item(ID _type, i64 _amt);
        Item(const Item & i) = default;
        Item(Item && i) = default;
        Item& operator=(const Item & i) = default;
        Item& operator=(Item && i) = default;

        ID GetType() const;
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
        bool HasItem(ID item_id);
        vec<Item>::iterator FindItem(ID item_id);
        void AddItem(Item i);
        bool AddDelivery(Delivery d);
        bool AddRequest(Request r);

        vec<Request> PassOnRequests(ID next_dest);
        vec<Delivery> PassOnDeliveries(ID next_dest);
        void CheckAndFillRequests();
        
    };


    /* Agent class */
    class Agent {
    private:
        ID id;
        vec<ID> nodes;
        vec<Request> requests;
        vec<Delivery> deliveries;
    public:
        
    };


}