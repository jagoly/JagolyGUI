#pragma once

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

namespace jagolygui {

template<class T> struct Vec2 {
    Vec2() : x(T(0)), y(T(0)) {}
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    Vec2(const Vec2<T>& _v) : x(_v.x), y(_v.y) {}
    inline const T* ptr() const { return &x; }
    union {T x, r;}; union {T y, g;};
};

using Vec2I = Vec2<int>; using Vec2U = Vec2<uint>; using Vec2F = Vec2<float>;

template<class T> inline Vec2<T> operator+(Vec2<T> _v, T _s) { return {_v.x+_s, _v.y+_s}; }
template<class T> inline Vec2<T> operator-(Vec2<T> _v, T _s) { return {_v.x-_s, _v.y-_s}; }
template<class T> inline Vec2<T> operator*(Vec2<T> _v, T _s) { return {_v.x*_s, _v.y*_s}; }
template<class T> inline Vec2<T> operator/(Vec2<T> _v, T _s) { return {_v.x/_s, _v.y/_s}; }

template<class T> inline Vec2<T> operator+=(Vec2<T>& _v, T _s) { return _v = {_v.x+_s, _v.y+_s}; }
template<class T> inline Vec2<T> operator-=(Vec2<T>& _v, T _s) { return _v = {_v.x-_s, _v.y-_s}; }
template<class T> inline Vec2<T> operator*=(Vec2<T>& _v, T _s) { return _v = {_v.x*_s, _v.y*_s}; }
template<class T> inline Vec2<T> operator/=(Vec2<T>& _v, T _s) { return _v = {_v.x/_s, _v.y/_s}; }

template<class T> inline Vec2<T> operator+(Vec2<T> _a, Vec2<T> _b) { return {_a.x+_b.x, _a.y+_b.y}; }
template<class T> inline Vec2<T> operator-(Vec2<T> _a, Vec2<T> _b) { return {_a.x-_b.x, _a.y-_b.y}; }
template<class T> inline Vec2<T> operator*(Vec2<T> _a, Vec2<T> _b) { return {_a.x*_b.x, _a.y*_b.y}; }
template<class T> inline Vec2<T> operator/(Vec2<T> _a, Vec2<T> _b) { return {_a.x/_b.x, _a.y/_b.y}; }

template<class T> inline Vec2<T> operator+=(Vec2<T>& _a, Vec2<T> _b) { return _a = {_a.x+_b.x, _a.y+_b.y}; }
template<class T> inline Vec2<T> operator-=(Vec2<T>& _a, Vec2<T> _b) { return _a = {_a.x-_b.x, _a.y-_b.y}; }
template<class T> inline Vec2<T> operator*=(Vec2<T>& _a, Vec2<T> _b) { return _a = {_a.x*_b.x, _a.y*_b.y}; }
template<class T> inline Vec2<T> operator/=(Vec2<T>& _a, Vec2<T> _b) { return _a = {_a.x/_b.x, _a.y/_b.y}; }

template<class T> inline Vec2<T> min2(Vec2<T> _a, Vec2<T> _b) { return {_a.x<_b.x ? _a.x:_b.x, _a.y<_b.y ? _a.y:_b.y}; }
template<class T> inline Vec2<T> max2(Vec2<T> _a, Vec2<T> _b) { return {_a.x>_b.x ? _a.x:_b.x, _a.y>_b.y ? _a.y:_b.y}; }

template<class T> inline bool less_equal(Vec2<T> _a, Vec2<T> _b) { return _a.x <= _b.x && _a.y <= _b.y; }
template<class T> inline bool more_equal(Vec2<T> _a, Vec2<T> _b) { return _a.x >= _b.x && _a.y >= _b.y; }

template<class T> inline bool operator==(Vec2<T> _a, Vec2<T> _b) { return _a.x == _b.x && _a.y == _b.y; }
template<class T> inline bool operator!=(Vec2<T> _a, Vec2<T> _b) { return _a.x != _b.x && _a.y != _b.y; }

}
