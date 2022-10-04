#pragma once

#include<string>

#include"defs.hpp"

class Time {
private:
    int day;
    int hour;
    int quarter;
public:
    Time();
    Time(int _day, int _hour, int _quarter);
    Time(const Time & t) = default;
    Time(Time && t) = default;
    Time& operator=(const Time & t) = default;
    Time& operator=(Time && t) = default;
    bool operator==(const Time & t);
    bool operator<(const Time & t);
    bool operator>(const Time & t);
    str ToString();
    int GetQuarter() const;
    int GetHour() const;
    int GetDay() const;

    void Tick();;
};