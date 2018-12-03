#pragma once

#include <cmath>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace Math {
    template <size_t d, class T>
    union Vec;

    template <class T>
    union Vec<2, T> final {
        T data[2];
        struct {
            T x, y;
        };
        struct {
            T less, last;
        };
        Vec() = default;
        constexpr Vec(T _x, T _y) noexcept
                :x(_x), y(_y) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(x+r.x, y+r.y); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(x-r.x, y-r.y); }
        template <class T2>
        constexpr Vec operator*(T2&& r) const noexcept { return Vec(x*std::forward<T2>(r), y*std::forward<T2>(r)); }
        template <class T2>
        constexpr Vec operator/(T2&& r) const noexcept { return Vec(x/std::forward<T2>(r), y/std::forward<T2>(r)); }
        Vec& operator+=(const Vec& r) noexcept {
            x += r.x;
            y += r.y;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            x -= r.x;
            y -= r.y;
            return *this;
        }
        template <class T2>
        Vec& operator*=(T2&& r) noexcept {
            x *= std::forward<T2>(r);
            y *= std::forward<T2>(r);
            return *this;
        }
        template <class T2>
        Vec& operator/=(T2&& r) noexcept {
            x /= std::forward<T2>(r);
            y /= std::forward<T2>(r);
            return *this;
        }
        constexpr T lengthSqr() const noexcept { return x*x+y*y; }
        constexpr bool operator==(const Vec& r) const noexcept { return (x==r.x) && (y==r.y); }
        constexpr bool operator<(const Vec& r) const noexcept { return lengthSqr()<r.lengthSqr(); }
        constexpr bool operator>(const Vec& r) const noexcept { return lengthSqr()>r.lengthSqr(); }
        constexpr bool operator<=(const Vec& r) const noexcept { return lengthSqr()<=r.lengthSqr(); }
        constexpr bool operator>=(const Vec& r) const noexcept { return lengthSqr()>=r.lengthSqr(); }
        constexpr T dot(const Vec& r) const noexcept { return x*r.x+y*r.y; }
        T length() noexcept { return sqrt(lengthSqr()); }
        template <class T2>
        explicit operator Vec<2, T2>() noexcept { return Vec<2, T2>(T2(x), T2(y)); }
    };

    template <class T>
    union Vec<3, T> final {
        T data[3];
        struct {
            T x, y, z;
        };
        struct {
            Vec<2, T> less;
            T last;
        };
        Vec() = default;
        constexpr Vec(T _x, T _y, T _z) noexcept
                :x(_x), y(_y), z(_z) { }
        constexpr Vec(const Vec<2, T>& ls, T arg) noexcept
                :less(ls), last(arg) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(x+r.x, y+r.y, z+r.z); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(x-r.x, y-r.y, z-r.z); }
        template <class T2>
        constexpr Vec operator*(T2&& r) const noexcept {
            return Vec(x*std::forward<T2>(r), y*std::forward<T2>(r), z*std::forward<T2>(r));
        }
        //cross product
        constexpr Vec operator*(const Vec& r) const noexcept { return Vec(y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x); }
        template <class T2>
        constexpr Vec operator/(T2&& r) const noexcept {
            return Vec(x/std::forward<T2>(r), y/std::forward<T2>(r), z/std::forward<T2>(r));
        }
        Vec& operator+=(const Vec& r) noexcept {
            x += r.x;
            y += r.y;
            z += r.z;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            x -= r.x;
            y -= r.y;
            z -= r.z;
            return *this;
        }
        template <class T2>
        Vec& operator*=(T2&& r) noexcept {
            x *= std::forward<T2>(r);
            y *= std::forward<T2>(r);
            z *= std::forward<T2>(r);
            return *this;
        }
        //cross product
        Vec& operator*=(const Vec& r) const noexcept {
            *this = Vec(y*r.z-z*r.y, z*r.x-x*r.z, x*r.y-y*r.x);
            return *this;
        }
        template <class T2>
        Vec& operator/=(T2&& r) noexcept {
            x /= std::forward<T2>(r);
            y /= std::forward<T2>(r);
            z /= std::forward<T2>(r);
            return *this;
        }
        constexpr T lengthSqr() const noexcept { return x*x+y*y+z*z; }
        constexpr bool operator==(const Vec& r) const noexcept { return (x==r.x) && (y==r.y) && (z==r.z); }
        constexpr bool operator<(const Vec& r) const noexcept { return lengthSqr()<r.lengthSqr(); }
        constexpr bool operator>(const Vec& r) const noexcept { return lengthSqr()>r.lengthSqr(); }
        constexpr bool operator<=(const Vec& r) const noexcept { return lengthSqr()<=r.lengthSqr(); }
        constexpr bool operator>=(const Vec& r) const noexcept { return lengthSqr()>=r.lengthSqr(); }
        constexpr T dot(const Vec& r) const noexcept { return x*r.x+y*r.y+z*r.z; }
        T length() noexcept { return sqrt(lengthSqr()); }
        template <class T2>
        explicit operator Vec<3, T2>() noexcept { return Vec<3, T2>(T2(x), T2(y), T2(z)); }
    };

    template <size_t d, class T>
    union Vec final {
        T data[d];
        struct {
            Vec<d-1, T> less;
            T last;
        };
        Vec() = default;
        template <class ...T2>
        constexpr Vec(const T& a1, T2&& ... args) noexcept
                :data{a1, std::forward<T2>(args)...} { }
        constexpr Vec(const Vec<d-1, T>& _less, const T& _last) noexcept
                :less(_less), last(_last) { }
        template <size_t d2, class ...T2>
        constexpr Vec(const Vec<d2, T>& ptr, const T& arg, const T& arg2, T2&& ...args) noexcept
                :Vec(Vec<d2+1, T>(ptr, arg), arg2, std::forward<T2>(args)...) { }
        constexpr Vec operator+(const Vec& r) const noexcept { return Vec(less+r.less, last+r.last); }
        constexpr Vec operator-(const Vec& r) const noexcept { return Vec(less-r.less, last-r.last); }
        template <class T2>
        constexpr Vec operator*(T2&& r) const noexcept { return Vec(less*std::forward<T2>(r), last*std::forward<T2>(r)); }
        template <class T2>
        constexpr Vec operator/(T2&& r) const noexcept { return Vec(less/std::forward<T2>(r), last/std::forward<T2>(r)); }
        Vec& operator+=(const Vec& r) noexcept {
            less += r.less;
            last += r.last;
            return *this;
        }
        Vec& operator-=(const Vec& r) noexcept {
            less -= r.less;
            last -= r.last;
            return *this;
        }
        template <class T2>
        Vec& operator*=(T2&& r) noexcept {
            less *= std::forward<T2>(r);
            last *= std::forward<T2>(r);
            return *this;
        }
        template <class T2>
        Vec& operator/=(T2&& r) noexcept {
            less /= std::forward<T2>(r);
            last /= std::forward<T2>(r);
            return *this;
        }
        constexpr T lengthSqr() const noexcept { return less.lengthSqr()+last*last; }
        constexpr bool operator==(const Vec& r) const noexcept { return (less==r.less) && (last==r.last); }
        constexpr bool operator<(const Vec& r) const noexcept { return lengthSqr()<r.lengthSqr(); }
        constexpr bool operator>(const Vec& r) const noexcept { return lengthSqr()>r.lengthSqr(); }
        constexpr bool operator<=(const Vec& r) const noexcept { return lengthSqr()<=r.lengthSqr(); }
        constexpr bool operator>=(const Vec& r) const noexcept { return lengthSqr()>=r.lengthSqr(); }
        constexpr T dot(const Vec& r) const noexcept { return less.dot(r.less)+last*r.last; }
        T length() noexcept { return sqrt(lengthSqr()); }
        template <class T2>
        explicit operator Vec<d, T2>() noexcept { return Vec<d, T2>(less, T2(last)); }
    };

    template <class T>
    using Vec2 = Vec<2, T>;
    using Vec2I = Vec2<int>;
    using Vec2F = Vec2<float>;
    using Vec2D = Vec2<double>;
    template <class T>
    using Vec3 = Vec<3, T>;
    using Vec3I = Vec3<int>;
    using Vec3F = Vec3<float>;
    using Vec3D = Vec3<double>;
}

namespace std {
    template <>
    struct hash<Math::Vec3I> {
        using argument_type = Math::Vec3I;
        using result_type = std::size_t;

        result_type operator()(argument_type const& s) const noexcept {
            size_t x = s.x;
            x = (x) & 0xFFFF00000000FFFF;
            x = (x | (x << 16)) & 0x00FF0000FF0000FF;
            x = (x | (x << 8)) & 0xF00F00F00F00F00F;
            x = (x | (x << 4)) & 0x30C30C30C30C30C3;
            x = (x | (x << 2)) & 0x9249249249249249;

            size_t y = s.y;
            y = (y) & 0xFFFF00000000FFFF;
            y = (y | (y << 16)) & 0x00FF0000FF0000FF;
            y = (y | (y << 8)) & 0xF00F00F00F00F00F;
            y = (y | (y << 4)) & 0x30C30C30C30C30C3;
            y = (y | (y << 2)) & 0x9249249249249249;

            size_t z = s.z;
            z = (z) & 0xFFFF00000000FFFF;
            z = (z | (z << 16)) & 0x00FF0000FF0000FF;
            z = (z | (z << 8)) & 0xF00F00F00F00F00F;
            z = (z | (z << 4)) & 0x30C30C30C30C30C3;
            z = (z | (z << 2)) & 0x9249249249249249;
            return x | (y << 1) | (z << 2);
        }
    };
}
