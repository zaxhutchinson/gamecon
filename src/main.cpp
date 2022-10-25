#include<iostream>
#include<vector>
#include<cstring>

#include"defs.hpp"
#include"sim.hpp"
//#include"gamecon.hpp"
//#include"gtime.hpp"

using namespace gcon;

void Test_001();

int main(int argc, char**argv) {

    Sim sim;
    sim.LoadTradeNetwork();
    sim.Loop(400);
    std::cout << sim.GetNetworkAsString() << std::endl;

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
    // owner->AddNode("House");
    // owner->AddNode("Store");
    uptr<Actor> farmer = std::make_unique<Actor>("Farmer");
    // farmer->AddNode("Farm");
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
    network.Update();
    network.ActorArrives("Owner","House","Store");
    network.Update();
    network.ActorLeaves("Farmer","Farm","Store");
    network.Update();
    network.ActorArrives("Farmer","Farm","Store");
    network.Update();
    network.ActorLeaves("Farmer","Store","Farm");
    network.Update();
    network.ActorArrives("Farmer","Store","Farm");
    network.Update();
    network.ActorLeaves("Farmer","Farm","Store");
    network.Update();
    network.ActorArrives("Farmer","Farm","Store");
    network.Update();
    network.ActorLeaves("Owner","Store","House");
    network.Update();
    network.ActorArrives("Owner","Store","House");

    network_str = network.ToString();
    std::cout << network_str << std::endl;

}