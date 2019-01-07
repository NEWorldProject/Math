#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    union Vec<3, T> {
        T Data[3];
        struct {
            T X, Y, Z;
        };
        constexpr Vec() noexcept
                :Data{T(0), T(0), T(0)} { }
        constexpr Vec(Vec&&) noexcept = default;
        constexpr Vec(const Vec&) noexcept = default;
        Vec& operator=(Vec&&) noexcept = default;
        Vec& operator=(const Vec&) noexcept = default;
        constexpr explicit Vec(VectorUninitializedT) noexcept
                :Data{} { }
        template <class Q, class W, class U>
        constexpr explicit Vec(Q&& arg0, W&& arg1, U&& args) noexcept
                :Data{static_cast<T>(std::forward<Q>(arg0)), static_cast<T>(std::forward<W>(arg1)),
                static_cast<T>(std::forward<U>(args))} { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<3, U>& r) noexcept
                :X(r.X), Y(r.Y), Z(r.Z) { }
        constexpr Vec operator-() const noexcept { return Vec(-X, -Y, -Z); }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y, Z+r.Z); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y, Z-r.Z); }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r, Z*r); }
        //cross product
        constexpr Vec operator*(const Vec& r) const noexcept { return Vec(Y*r.Z-Z*r.Y, Z*r.X-X*r.Z, X*r.Y-Y*r.X); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r, Z/r); }
        constexpr auto& operator[](size_t index) noexcept { return Data[index]; }
        constexpr auto& operator[](size_t index) const noexcept { return Data[index]; }
        Vec& operator+=(const Vec& r) noexcept {
            X += r.X;
            Y += r.Y;
            Z += r.Z;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            X -= r.X;
            Y -= r.Y;
            Z -= r.Z;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Vec& operator*=(const U& r) noexcept {
            X *= r;
            Y *= r;
            Z *= r;
            return *this;
        }
        //cross product
        Vec& operator*=(const Vec& r) const noexcept {
            *this = Vec(Y*r.Z-Z*r.Y, Z*r.X-X*r.Z, X*r.Y-Y*r.X);
            return *this;
        }
        template <class U>
        Vec& operator/=(const U& r) noexcept {
            X /= r;
            Y /= r;
            Z /= r;
            return *this;
        }
        constexpr T LengthSqr() const noexcept { return X*X+Y*Y+Z*Z; }
        constexpr bool operator==(const Vec& r) const noexcept { return (X==r.X) && (Y==r.Y) && (Z==r.Z); }
        constexpr T Dot(const Vec& r) const noexcept { return X*r.X+Y*r.Y+Z*r.Z; }
        T Length() noexcept { return sqrt(LengthSqr()); }
    };

    template <class T>
    using Vec3 = Vec<3, T>;
    using Vec3I = Vec3<int>;
    using Vec3B = Vec3<int8_t>;
    using Vec3S = Vec3<int16_t>;
    using Vec3L = Vec3<int32_t>;
    using Vec3LL = Vec3<int64_t>;
    using Vec3F = Vec3<float>;
    using Vec3D = Vec3<double>;
    using Vec3ED = Vec3<long double>;
}

namespace std {
    template <>
    struct hash<Math::Vec3I> {
        using argument_type = Math::Vec3I;
        using result_type = std::size_t;

        result_type operator()(argument_type const& s) const noexcept {
            size_t x = s.X;
            x = (x) & 0xFFFF00000000FFFF;
            x = (x | (x << 16)) & 0x00FF0000FF0000FF;
            x = (x | (x << 8)) & 0xF00F00F00F00F00F;
            x = (x | (x << 4)) & 0x30C30C30C30C30C3;
            x = (x | (x << 2)) & 0x9249249249249249;

            size_t y = s.Y;
            y = (y) & 0xFFFF00000000FFFF;
            y = (y | (y << 16)) & 0x00FF0000FF0000FF;
            y = (y | (y << 8)) & 0xF00F00F00F00F00F;
            y = (y | (y << 4)) & 0x30C30C30C30C30C3;
            y = (y | (y << 2)) & 0x9249249249249249;

            size_t z = s.Z;
            z = (z) & 0xFFFF00000000FFFF;
            z = (z | (z << 16)) & 0x00FF0000FF0000FF;
            z = (z | (z << 8)) & 0xF00F00F00F00F00F;
            z = (z | (z << 4)) & 0x30C30C30C30C30C3;
            z = (z | (z << 2)) & 0x9249249249249249;
            return x | (y << 1) | (z << 2);
        }
    };
}
