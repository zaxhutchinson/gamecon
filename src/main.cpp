#include<iostream>
#include<vector>
#include<cstring>

#include"defs.hpp"
#include"gamecon.hpp"
#include"gtime.hpp"

using namespace gcon;

void Test_001();

int main(int argc, char**argv) {

    Time t1(2,1,2);
    Time t2(1,4,3);
    std::cout << (t1 - t2).ToString() << std::endl;

    std::cout << t1.ToString() << std::endl;
    std::cout << t2.ToString() << std::endl;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"001")==0) Test_001();
    }

    return 0;
}


void Test_001() {


    uptr<Node> house = std::make_unique<Node>("House");
    uptr<Node> farm = std::make_unique<Node>("Farm");
    uptr<Node> store = std::make_unique<Node>("Store");

    uptr<Actor> owner = std::make_unique<Actor>("Owner");
    owner->AddNode("House");
    owner->AddNode("Store");
    uptr<Actor> farmer = std::make_unique<Actor>("Farmer");
    farmer->AddNode("Farm");
    // farmer->AddDeliveries("Store");

    Item item("Carrot",10);
    farm->AddItem(item);
    house->InitiateRequest(item);

    Network network;

    network.RegisterNode(std::move(house));
    network.RegisterNode(std::move(farm));
    network.RegisterNode(std::move(store));
    network.RegisterActor(std::move(owner));
    network.RegisterActor(std::move(farmer));

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