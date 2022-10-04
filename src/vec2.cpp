#include"vec2.hpp"


Vec2::Vec2() {
    x = 0.0;
    y = 0.0;
}
Vec2::Vec2(double _x, double _y) {
    x = _x;
    y = _y;
}
double Vec2::X() const {
    return x;
}
void Vec2::X(double _x) {
    x = _x;
}
double Vec2::Y() const {
    return y;
}
void Vec2::Y(double _y) {
    y = _y;
}
double Vec2::Distance(const Vec2 & v) {
    return std::sqrt(
        std::pow(v.X()-x, 2.0) + std::pow(v.Y()-y, 2.0)
    );
}