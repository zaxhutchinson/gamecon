#pragma once
#include<cmath>
#include"defs.hpp"

class Vec2 {
private:
    double x;
    double y;
public:
    Vec2();
    Vec2(double _x, double _y);
    Vec2(vec<double> & v);
    Vec2(const Vec2 & v) = default;
    Vec2(Vec2 && v) = default;
    Vec2& operator=(const Vec2 & v) = default;
    Vec2& operator=(Vec2 && v) = default;
    double X() const;
    void X(double _x);
    double Y() const;
    void Y(double _y);
    double Distance(const Vec2 & v);
};
