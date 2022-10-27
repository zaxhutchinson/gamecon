#include<iostream>
#include<vector>
#include<cstring>
#include<cstdint>

#include"defs.hpp"
#include"sim.hpp"
//#include"gamecon.hpp"
//#include"gtime.hpp"

using namespace gcon;


int main(int argc, char**argv) {

    // vec<int> v = {0,1,2,3,4,5,6,7,8,9};
    // for(vec<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ) {
    //     if((*rit)!=5) {
    //         std::advance(rit,1);
    //         v.erase(rit.base());
    //     } else {
    //         v.erase(std::next(rit).base());
    //         break;
    //     }
    // }
    // for(sizet i = 0; i < v.size(); i++) {
    //     std::cout << v[i] << std::endl;
    // }



    str filename = "scen"+str(argv[1])+".json";
    Sim sim;
    sim.LoadTradeNetwork(filename);
    sim.Loop(std::stoi(argv[2]));
    std::cout << sim.GetNetworkAsString() << std::endl;

    return 0;
}

// house = std::make_unique<Node>("House");
//     uptr<Node> farm = std::make_unique<Node>("Farm");
//     uptr<Node> store = std::make_unique<Node>("Store");

//     uptr<Actor> owner = std::make_unique<Actor>("Owner");
//     // owner->AddNode("House");
//     // owner->AddNode("Store");
//     uptr<Actor> farmer = std::make_unique<Actor>("Farmer");
//     // farmer->AddNode("Farm");
//     // farmer->AddDeliveries("Store");

//     Item item("Carrot",10);
//     farm->AddItem(item);
//     house->InitiateRequest(item);

//     Network network;

//     network.RegisterNode(std::move(house));
//     network.RegisterNode(std::move(farm));
//     network.RegisterNode(std::move(store));
//     network.RegisterActor(std::move(owner));
//     network.RegisterActor(std::move(farmer));

//     network.RefreshNetwork();

//     str network_str = network.ToString();
//     std::cout << network_str << std::endl;

//     network.ActorLeaves("Owner","House","Store");
//     network.Update();
//     network.ActorArrives("Owner","House","Store");
//     network.Update();
//     network.ActorLeaves("Farmer","Farm","Store");
//     network.Update();
//     network.ActorArrives("Farmer","Farm","Store");
//     network.Update();
//     network.ActorLeaves("Farmer","Store","Farm");
//     network.Update();
//     network.ActorArrives("Farmer","Store","Farm");
//     network.Update();
//     network.ActorLeaves("Farmer","Farm","Store");
//     network.Update();
//     network.ActorArrives("Farmer","Farm","Store");
//     network.Update();
//     network.ActorLeaves("Owner","Store","House");
//     network.Update();
//     network.ActorArrives("Owner","Store","House");

//     network_str = network.ToString();
//     std::cout << network_str << std::endl;

// }