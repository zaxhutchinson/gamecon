#include<iostream>

#include"gamecon.hpp"

int main(int argc, char**argv) {

    gcon::Item i(0, 10);

    std::cout << i.GetAmt() << std::endl;


    return 0;
}