#include<iostream>
#include<vector>

#include"gamecon.hpp"

int main(int argc, char**argv) {

    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};

    for(
        std::vector<int>::reverse_iterator rit = v.rbegin();
        rit != v.rend();
    ) {
        if(*rit>5) {
            std::advance(rit,1);
            v.erase(rit.base());
        } else {
            v.erase(std::next(rit).base());
            break;
        }
    }

    for(size_t i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    std::cout << std::endl;


    return 0;
}