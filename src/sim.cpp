#include"sim.hpp"

/*---------------------------------------------*/
// TIME

Time::Time()
    : quarter(0), hour(0), day(0)
{}

Time::Time(int _quarter, int _hour, int _day)
    : quarter(_quarter), hour(_hour), day(_day)
{}

int Time::GetQuarter() const {
    return quarter;
}
int Time::GetHour() const {
    return hour;
}
int Time::GetDay() const {
    return day;
}

void Time::Tick() {
    quarter++;
    if(quarter>=4) {
        quarter=0;
        hour++;
        if(hour >= 24) {
            hour=0;
            day++;
        }
    }
}

/*---------------------------------------------*/