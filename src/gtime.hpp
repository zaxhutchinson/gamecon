#pragma once

#include<string>

#include"defs.hpp"

class Time {
private:
    static constexpr int QTRS_IN_HOUR = 4;
    static constexpr int HRS_IN_DAY = 24;
    static constexpr int QTRS_IN_DAY = QTRS_IN_HOUR*HRS_IN_DAY;
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
    Time& operator-=(const Time & t);
    friend Time operator-(Time t, const Time & s);
    str ToString();
    int GetQuarter() const;
    int GetHour() const;
    int GetDay() const;
    int GetAsQuarters();
    void Tick();
};