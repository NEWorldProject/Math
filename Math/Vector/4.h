#pragma once

#include "Base.h"

namespace Math {
    template <class V>
    union Vec<4, V> {
        V Data[4];
        struct {
            V X, Y, Z, T;
        };
        constexpr Vec() noexcept
                :Data{V(0), V(0), V(0), V(0)} { }
        constexpr Vec(Vec&&) noexcept = default;
        constexpr Vec(const Vec&) noexcept = default;
        Vec& operator=(Vec&&) noexcept = default;
        Vec& operator=(const Vec&) noexcept = default;
        constexpr explicit Vec(VectorUninitializedT) noexcept
                :Data{} { }
        template <class Q, class W, class ...U>
        constexpr explicit Vec(Q&& arg0, W&& arg1, U&& ... args) noexcept
                :Data{static_cast<V>(std::forward<Q>(arg0)), static_cast<V>(std::forward<W>(arg1)),
                static_cast<V>(std::forward<U>(args))...} { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, V>>>
        constexpr explicit Vec(const Vec<4, U>& r) noexcept
                :X(r.X), Y(r.Y), Z(r.Z), T(r.T) { }
        constexpr Vec operator-() const noexcept { return Vec(-X, -Y, -Z, -T); }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y, Z+r.Z, T+r.T); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y, Z-r.Z); }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r, Z*r, T*r); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r, Z/r, T/r); }
        constexpr auto& operator[](size_t index) noexcept { return Data[index]; }
        constexpr auto& operator[](size_t index) const noexcept { return Data[index]; }
        Vec& operator+=(const Vec& r) noexcept {
            X += r.X;
            Y += r.Y;
            Z += r.Z;
            T += r.T;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            X -= r.X;
            Y -= r.Y;
            Z -= r.Z;
            T -= r.T;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Vec& operator*=(const U& r) noexcept {
            X *= r;
            Y *= r;
            Z *= r;
            T *= r;
            return *this;
        }
        template <class U>
        Vec& operator/=(const U& r) noexcept {
            X /= r;
            Y /= r;
            Z /= r;
            T /= r;
            return *this;
        }
        constexpr V LengthSqr() const noexcept { return X*X+Y*Y+Z*Z+T*T; }
        constexpr bool operator==(const Vec& r) const noexcept { return (X==r.T) && (Y==r.T) && (Z==r.T) && (T==r.T); }
        constexpr V Dot(const Vec& r) const noexcept { return X*r.X+Y*r.Y+Z*r.Z+T*r.T; }
        V Length() noexcept { return sqrt(LengthSqr()); }
    };

    template <class T>
    using Vec4 = Vec<4, T>;
    using Vec4I = Vec4<int>;
    using Vec4B = Vec4<int8_t>;
    using Vec4S = Vec4<int16_t>;
    using Vec4L = Vec4<int32_t>;
    using Vec4LL = Vec4<int64_t>;
    using Vec4F = Vec4<float>;
    using Vec4D = Vec4<double>;
    using Vec4ED = Vec4<long double>;
}
