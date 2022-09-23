#include<string>
#include<memory>
#include<cstdint>
#include<mutex>
#include<vector>

namespace gcon {

    /* Aliases */
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
        Item(const Request & r);

        ID GetType() const;
        i64 GetAmt() const;
        void SetAmt(i64 a);
    };

    /* Request */
    class Request {
    private:
        ID type;
        i64 amt;
        vec<ID> route;
    public:
        Request();
        Request(ID _type);
        Request(ID _type, i64 _amt);
        Request(const Request & r) = default;
        Request(Request && r) = default;
        Request& operator=(const Request & r) = default;
        Request& operator=(Request && r) = default;
        Request(const Item & i);
        ID GetType() const;
        i64 GetAmt() const;
    };



    class Node {
    private:
        ID id;
        vec<Item> items;
        vec<Request> requests;
    public:
        Node();
        Node(ID _id);
        ID GetID() const;
        void AddItem(Item i);
    };


    /* Agent class */
    class Agent {
    private:
        ID id;
        vec<ID> node_ids;
    public:
        
    };


}