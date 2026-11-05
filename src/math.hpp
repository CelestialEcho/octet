#pragma once

namespace oc {

struct Vec2 {
    float x, y;

    Vec2( const float& x, const float& y ) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(const float& scalar) const { return Vec2(x * scalar, y * scalar); }

    Vec2& operator+=(const Vec2& other) { return *this = *this + other; }
    Vec2& operator-=(const Vec2& other) { return *this = *this - other; }
    Vec2& operator*=(const float& scalar) { return *this = *this * scalar; }
};
    
}