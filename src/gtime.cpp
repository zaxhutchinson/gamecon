#include"gtime.hpp"


/*---------------------------------------------*/
// TIME

Time::Time()
    : day(0), hour(0), quarter(0)
{}

Time::Time(int _day, int _hour, int _quarter)
    : day(_day), hour(_hour), quarter(_quarter)
{}
bool Time::operator==(const Time & t) {
    return day==t.day && hour==t.hour && quarter==t.quarter;
}
bool Time::operator<(const Time & t) {
    if(day==-1 || t.day==-1) {

        if(hour == -1 || t.hour==-1) {
            if(quarter < t.quarter) return true;
            else {
                return false;
            }
        } else {

            if(hour < t.hour) return true;
            else if(hour == t.hour) {
                if(quarter < t.quarter) return true;
                else {
                    return false;
                }
            } else {
                return false;
            }
        }
    } else {

        if(day < t.day) return true;
        else if(day == t.day) {
            if(hour < t.hour) return true;
            else if(hour == t.hour) {
                if(quarter < t.quarter) return true;
                else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } 
}
bool Time::operator>(const Time & t) {
    return !(*this==t && *this<t);
}
str Time::ToString() {
    std::stringstream ss;
    ss << day << " - " << hour << " - " << quarter;
    return ss.str();
}
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