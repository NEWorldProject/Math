#pragma once

#include "Vector.h"

namespace Math {
    struct AARect {
        constexpr AARect(const int width, const int height) noexcept
                :Left(0), Top(0), Width(width), Height(height) { }
        constexpr AARect(const int left, const int top, const int width, const int height) noexcept
                :Left(left), Top(top), Width(width), Height(height) { }
        constexpr explicit AARect(const Vec2I& size) noexcept
                :AARect(size.X, size.Y) { }
        constexpr AARect(const Vec2I& echo, const Vec2I& size) noexcept
                :AARect(echo.X, echo.Y, size.X, size.Y) { }
        constexpr Vec2I Echo() const noexcept { return Vec2I(Left, Top); }
        constexpr Vec2I Size() const noexcept { return Vec2I(Width, Height); }
        auto& Expand(const Vec2I& delta) noexcept {
            Width += delta.X;
            Height += delta.Y;
            return *this;
        }
        auto& Include(const Vec2I& point) noexcept {
            const auto dt = point - Echo();
            if (dt.X < 0)
                Left = point.X;
            else if (dt.X > Width)
                Width = dt.X;
            if (dt.Y < 0)
                Top = point.Y;
            else if (dt.Y > Height)
                Height = dt.Y;
            return *this;
        }
        auto& Include(int x, int y) noexcept { return Include(Vec2I(x, y)); }
        auto& Merge(const AARect& rect) noexcept { return Include(rect.Echo()).Include(rect.Echo() + rect.Size()); }
        auto& Move(const Vec2I& delta) noexcept {
            Left += delta.X;
            Top += delta.Y;
            return *this;
        }
        int Left, Top, Width, Height;
    };
}
