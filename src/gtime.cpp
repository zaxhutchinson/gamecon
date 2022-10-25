#include"gtime.hpp"


/*---------------------------------------------*/
// TIME

Time::Time()
    : day(0), hour(0), quarter(0)
{}

Time::Time(int _day, int _hour, int _quarter)
{
    quarter = _quarter;
    hour = _hour;
    day = _day;
    hour += _quarter / QTRS_IN_HOUR;
    quarter = _quarter % QTRS_IN_HOUR;
    day += hour / HRS_IN_DAY;
    hour = hour % HRS_IN_DAY;
}
Time::Time(vec<int> & v) {
    if(v.size() < 3) {
        day = 0;
        hour = 0;
        quarter = 0;
    } else {
        day = v[0];
        hour = v[1];
        quarter = v[2];
    }
}
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
bool Time::operator<=(const Time & t) {
    return (*this < t) || (*this==t);
}
bool Time::operator>=(const Time & t) {
    return (*this > t) || (*this==t);
}    
Time& Time::operator-=(const Time & t) {
    if(this->quarter < t.quarter) {
        this->quarter += QTRS_IN_HOUR;
        this->hour -= 1;
    }
    if(this->hour < t.hour) {
        this->hour += HRS_IN_DAY;
        this->day -= 1;
    }

    this->quarter -= t.quarter;
    this->hour -= t.hour;
    this->day -= t.day;

    return *this;
}
Time operator-(Time t, const Time & s) {
    t -= s;
    return t;
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

int Time::GetAsQuarters() {
    return  quarter +
            hour*QTRS_IN_HOUR +
            day*QTRS_IN_DAY;
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