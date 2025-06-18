#pragma once

struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float xVal, float yVal) : x(xVal), y(yVal) {}
};

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}
};

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float xVal, float yVal, float zVal, float wVal) : x(xVal), y(yVal), z(zVal), w(wVal) {}
};


