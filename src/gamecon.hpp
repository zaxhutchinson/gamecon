#include<string>
#include<memory>
#include<cstdint>
#include<mutex>

namespace gcon {

    /* Aliases */
    using str = std::string;
    template<typename T>
    using sptr = std::shared_ptr<T>;
    using i64 = int64_t;
    template<typename T>
    using vec = std::vector<T>;

    /* Item  */
    template<class T=i64, class U=i64>
    class Item {
    private:
        T type;
        i64 amt;
        bool is_request;
        U dest_id;
    public:
        Item() { amt = 0; }
        Item(T _type) { type = _type; amt = 0; is_request = false;}
        Item(T _type, i64 _amt) { type = _type; amt = _amt; is_request = false;}
        Item(T _type, i64 _amt, U _dest_id) { 
            type = _type; 
            amt = _amt;
            is_request = true;
            dest_id = _dest_id; 
        }
        T GetType() { return type; }
        i64 GetAmt() { return amt; }
        void SetAmt(i64 a) { amt = a; }
        bool IsRequest() { return is_request; }
        void SetRequest(bool r) { is_request = r; }
        void CloseRequest() { is_request = false; }
        U GetDestID() { return dest_id; }
    };

    template<class T=i64>
    class Node {
    private:
        T id;
        vec<Item> items;
    };


}