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

    Actor owner("Owner");
    owner.AddNode("House");
    owner.AddNode("Store");
    Actor farmer("Farmer");
    farmer.AddNode("Farm");
    farmer.AddNode("Store");

    Item item("Carrot",10);
    farm.AddItem(item);
    house.InitiateRequest(item);

    Network network;

    network.RegisterNode(house);
    network.RegisterNode(farm);
    network.RegisterNode(store);
    network.RegisterActor(owner);
    network.RegisterActor(farmer);

    network.RefreshNetwork();

    str network_str = network.ToString();
    std::cout << network_str << std::endl;

    network.ActorLeaves("Owner","House","Store");
    network.ActorArrives("Owner","House","Store");
    network.ActorLeaves("Farmer","Farm","Store");
    network.ActorArrives("Farmer","Farm","Store");
    network.ActorLeaves("Farmer","Store","Farm");
    network.ActorArrives("Farmer","Store","Farm");
    network.ActorLeaves("Farmer","Farm","Store");
    network.ActorArrives("Farmer","Farm","Store");
    network.ActorLeaves("Owner","Store","House");
    network.ActorArrives("Owner","Store","House");

    network_str = network.ToString();
    std::cout << network_str << std::endl;

}