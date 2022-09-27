#pragma once

#include"gamecon.hpp"

using namespace gcon;

/*---------------------------------------------*/

class Time {
private:
    int quarter;
    int hour;
    int day;
public:
    Time();
    Time(int _quarter, int _hour, int _day);
    Time(const Time & t) = default;
    Time(Time && t) = default;
    Time& operator=(const Time & t) = default;
    Time& operator=(Time && t) = default;

    int GetQuarter() const;
    int GetHour() const;
    int GetDay() const;

    void Tick();

};

/*---------------------------------------------*/

class Sim {
private:
    Time time;
    TradeNetwork tn;
public:
    Sim();
    void BuildTradeNetwork();
    void Loop();
    void Tick();

};