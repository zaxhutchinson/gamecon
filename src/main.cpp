#include<iostream>
#include<vector>
#include<cstring>

#include"defs.hpp"
#include"gamecon.hpp"
#include"gtime.hpp"

using namespace gcon;

void Test_001();

int main(int argc, char**argv) {

    Time t1(-1,0,6);
    Time t2(1,-1,6);
    std::cout << (t1 < t2) << std::endl;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"001")==0) Test_001();
    }

    return 0;
}


void Test_001() {


    Node house("House");
    Node farm("Farm");
    Node store("Store");

    Trader owner("Owner");
    owner.AddNode("House");
    owner.AddNode("Store");
    Trader farmer("Farmer");
    farmer.AddNode("Farm");
    farmer.AddNode("Store");

    Item item("Carrot",10);
    farm.AddItem(item);
    house.InitiateRequest(item);

    TradeNetwork network;

    network.RegisterNode(house);
    network.RegisterNode(farm);
    network.RegisterNode(store);
    network.RegisterTrader(owner);
    network.RegisterTrader(farmer);

    network.RefreshNetwork();

    str network_str = network.ToString();
    std::cout << network_str << std::endl;

    network.TraderLeaves("Owner","House","Store");
    network.TraderArrives("Owner","House","Store");
    network.TraderLeaves("Farmer","Farm","Store");
    network.TraderArrives("Farmer","Farm","Store");
    network.TraderLeaves("Farmer","Store","Farm");
    network.TraderArrives("Farmer","Store","Farm");
    network.TraderLeaves("Farmer","Farm","Store");
    network.TraderArrives("Farmer","Farm","Store");
    network.TraderLeaves("Owner","Store","House");
    network.TraderArrives("Owner","Store","House");

    network_str = network.ToString();
    std::cout << network_str << std::endl;

}