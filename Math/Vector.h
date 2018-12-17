#pragma once

#include <cmath>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace Math {
    template <size_t D, class T>
    union Vec;

    template <class T>
    union Vec<2, T> {
        T Data[2];
        struct {
            T X, Y;
        };
        constexpr Vec() = default;
        constexpr Vec(T x, T y) noexcept
                :X(x), Y(y) { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<3, U>& r) noexcept
                :X(r.X), Y(r.Y) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y); }
        template <class U>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r); }
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
        template <class U>
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
    union Vec<3, T> {
        T Data[3];
        struct {
            T X, Y, Z;
        };
        constexpr Vec() = default;
        constexpr Vec(T x, T y, T z) noexcept
                :X(x), Y(y), Z(z) { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<3, U>& r) noexcept
                :X(r.X), Y(r.Y), Z(r.Z) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y, Z+r.Z); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y, Z-r.Z); }
        template <class U>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r, Z*r); }
        //cross product
        constexpr Vec operator*(const Vec& r) const noexcept { return Vec(Y*r.Z-Z*r.Y, Z*r.X-X*r.Z, X*r.Y-Y*r.X); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r, Z/r); }
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
        template <class U>
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

    template <class V>
    union Vec<4, V> {
        V Data[4];
        struct {
            V X, Y, Z, T;
        };
        constexpr Vec() = default;
        constexpr Vec(V x, V y, V z, V t) noexcept
                :X(x), Y(y), Z(z), T(t) { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, V>>>
        constexpr explicit Vec(const Vec<4, U>& r) noexcept
                :X(r.X), Y(r.Y), Z(r.Z), T(r.T) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(X+r.X, Y+r.Y, Z+r.Z, T+r.T); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(X-r.X, Y-r.Y, Z-r.Z); }
        template <class U>
        constexpr Vec operator*(const U& r) const noexcept { return Vec(X*r, Y*r, Z*r, T*r); }
        template <class U>
        constexpr Vec operator/(const U& r) const noexcept { return Vec(X/r, Y/r, Z/r, T/r); }
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
        template <class U>
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

    template <size_t D, class T>
    union Vec {
        T Data[D];
        constexpr Vec() = default;
        template <class ...U>
        constexpr explicit Vec(U&& ... args) noexcept
                :Data{std::forward<U>(args)...} { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<D, U>& r) noexcept
                : Data{} {
            for (auto i = 0u; i<D; ++i) Data[i] = static_cast<T>(r.Data[i]);
        }
        constexpr Vec operator+(const Vec& r) const noexcept {
            Vec ret{};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]+r.Data[i];
            return ret;
        }
        constexpr Vec operator-(const Vec& r) const noexcept {
            Vec ret{};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]-r.Data[i];
            return ret;
        }
        template <class U>
        constexpr Vec operator*(U&& r) const noexcept {
            Vec ret{};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]*r;
            return ret;
        }
        template <class U>
        constexpr Vec operator/(U&& r) const noexcept {
            Vec ret{};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]/r;
            return ret;
        }
        Vec& operator+=(const Vec& r) noexcept {
            for (auto i = 0u; i<D; ++i) Data[i] += r.Data[i];
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            for (auto i = 0u; i<D; ++i) Data[i] -= r.Data[i];
            return *this;
        }
        template <class U>
        Vec& operator*=(U&& r) noexcept {
            for (auto i = 0u; i<D; ++i) Data[i] *= r.Data[i];
            return *this;
        }
        template <class U>
        Vec& operator/=(U&& r) noexcept {
            for (auto i = 0u; i<D; ++i) Data[i] /= r.Data[i];
            return *this;
        }
        constexpr T LengthSqr() const noexcept {
            T
            ret{0};
            for (auto i = 0u; i<D; ++i) ret += Data[i]*Data[i];
            return ret;
        }
        constexpr bool operator==(const Vec& r) const noexcept {
            bool ret = true;
            for (auto i = 0u; i<D; ++i) ret &= Data[i]==r.Data[i];
            return ret;
        }
        constexpr T Dot(const Vec& r) const noexcept {
            T
            ret{0};
            for (auto i = 0u; i<D; ++i) ret += Data[i]*r.Data[i];
            return ret;
        }
        T Length() noexcept { return sqrt(LengthSqr()); }
    };

    template <size_t D, class T>
    constexpr bool operator<(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()<r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator>(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()>r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator<=(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()<=r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator>=(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()>=r.LengthSqr(); }
    template <size_t D, class T, class U>
    constexpr auto operator*(const U& l, const Vec<D, T>& r) noexcept { return r*l; } // vec * n == n * vec
    template <size_t D, class T>
    constexpr auto Dot(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return l.Dot(r); }

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
