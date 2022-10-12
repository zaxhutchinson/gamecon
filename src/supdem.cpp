#include"supdem.hpp"


Event::Event() 
    : item(gcon::Item()), probability(0.0), freqency(Time())
{}
Event::Event(gcon::Item _item, double _prob, Time _freq) 
    : item(_item), probability(_prob), freqency(_freq)
{}

gcon::Item Event::GetItem() const {
    return item;
}

double Event::GetProbability() const {
    return probability;
}

Time Event::GetFrequency() const {
    return freqency;
}

opt<gcon::Item> Event::Check(RNG * rng, Time & curtime) {
    
    double actual_prob = (curtime-last_event).GetAsQuarters() / 
                static_cast<double>(freqency.GetAsQuarters());

    std::uniform_real_distribution<double> d(0.0,1.0);

    if(d(*rng) < actual_prob) {
        return {item};
    } else {
        return std::nullopt;
    }
}




