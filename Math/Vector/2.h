#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    union Vec<2, T> {
        T Data[2];
        struct {
            T X, Y;
        };
        constexpr Vec() noexcept: Data{T(0), T(0)} {}
        constexpr Vec(Vec&&) noexcept = default;
        constexpr Vec(const Vec&) noexcept = default;
        Vec& operator=(Vec&&) noexcept = default;
        Vec& operator=(const Vec&) noexcept = default;
        constexpr explicit Vec(VectorUninitializedT) noexcept : Data{} {}
        template <class Q, class U>
        constexpr explicit Vec(Q&& arg0, U&& args) noexcept
                :Data{static_cast<T>(std::forward<Q>(arg0)), static_cast<T>(std::forward<U>(args))} { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<3, U>& r) noexcept
                :X(r.X), Y(r.Y) { }
        constexpr Vec operator-() const noexcept { return Vec(-X, -Y); }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y); }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r); }
        constexpr auto& operator[](size_t index) noexcept { return Data[index]; }
        constexpr auto& operator[](size_t index) const noexcept { return Data[index]; }
        Vec& operator+=(const Vec& r) noexcept {
            X += r.X;
            Y += r.Y;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            X -= r.X;
            Y -= r.Y;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Vec& operator*=(const U& r) noexcept {
            X *= r;
            Y *= r;
            return *this;
        }
        template <class U>
        Vec& operator/=(const U& r) noexcept {
            X /= r;
            Y /= r;
            return *this;
        }
        constexpr T LengthSqr() const noexcept { return X*X+Y*Y; }
        constexpr bool operator==(const Vec& r) const noexcept { return (X==r.X) && (Y==r.Y); }
        constexpr T Dot(const Vec& r) const noexcept { return X*r.X+Y*r.Y; }
        T Length() noexcept { return sqrt(LengthSqr()); }
    };

    template <class T>
    using Vec2 = Vec<2, T>;
    using Vec2I = Vec2<int>;
    using Vec2B = Vec2<int8_t>;
    using Vec2S = Vec2<int16_t>;
    using Vec2L = Vec2<int32_t>;
    using Vec2LL = Vec2<int64_t>;
    using Vec2F = Vec2<float>;
    using Vec2D = Vec2<double>;
    using Vec2ED = Vec2<long double>;
}
