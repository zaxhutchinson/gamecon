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

    class Request;

    /* Item  */
    class Item {
    private:
        ID type;
        i64 amt;
    public:
        Item() { amt = 0; }
        Item(ID _type) { type = _type; amt = 0;}
        Item(ID _type, i64 _amt) { type = _type; amt = _amt;}
        Item(const Request & r) {
            type = r.GetType();
            amt = r.GetAmt();
        }

        ID GetType() const { return type; }
        i64 GetAmt() const { return amt; }
        void SetAmt(i64 a) { amt = a; }
    };

    /* Request */
    class Request {
    private:
        ID type;
        i64 amt;
        vec<ID> route;
    public:
        Request() { amt = 0; }
        Request(ID _type) { type = _type; amt = 0; }
        Request(ID _type, i64 _amt) { type = _type; amt = _amt; }
        Request(const Item & i) {
            type = i.GetType();
            amt = i.GetAmt();
        }
        ID GetType() const { return type; }
        i64 GetAmt() const { return amt; }
    };



    class Node {
    private:
        ID id;
        vec<Item> items;
    public:
        Node() {}
        Node(ID _id) { id = _id; }
        ID GetID() { return id; }
        void AddItem(Item i) {

        }
    };


}