#pragma once

#include "Base.h"

namespace Math {
    template <size_t D, class T>
    union Vec {
        T Data[D];
        constexpr Vec() noexcept
                :Data{} { for (auto i = 0u; i<D; ++i) Data[i] = T(0); }
        constexpr explicit Vec(VectorUninitializedT) noexcept
                :Data{} { }
        template <class ...U>
        constexpr explicit Vec(U&& ... args) noexcept
                :Data{static_cast<T>(std::forward<U>(args))...} { }
        template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
        constexpr explicit Vec(const Vec<D, U>& r) noexcept
                : Data{} {
            for (auto i = 0u; i<D; ++i) Data[i] = static_cast<T>(r.Data[i]);
        }
        constexpr Vec operator-() const noexcept {
            Vec ret{VectorUninitialized};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = -Data[i];
            return ret;
        }
        constexpr Vec operator+(const Vec& r) const noexcept {
            Vec ret{VectorUninitialized};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]+r.Data[i];
            return ret;
        }
        constexpr Vec operator-(const Vec& r) const noexcept {
            Vec ret{VectorUninitialized};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]-r.Data[i];
            return ret;
        }
        template <class U>
        constexpr Vec operator*(U&& r) const noexcept {
            Vec ret{VectorUninitialized};
            for (auto i = 0u; i<D; ++i) ret.Data[i] = Data[i]*r;
            return ret;
        }
        template <class U>
        constexpr Vec operator/(U&& r) const noexcept {
            Vec ret{VectorUninitialized};
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
            T ret{0};
            for (auto i = 0u; i<D; ++i) ret += Data[i]*Data[i];
            return ret;
        }
        constexpr bool operator==(const Vec& r) const noexcept {
            bool ret = true;
            for (auto i = 0u; i<D; ++i) ret &= Data[i]==r.Data[i];
            return ret;
        }
        constexpr T Dot(const Vec& r) const noexcept {
            T ret{0};
            for (auto i = 0u; i<D; ++i) ret += Data[i]*r.Data[i];
            return ret;
        }
        T Length() noexcept { return sqrt(LengthSqr()); }
    };
}
