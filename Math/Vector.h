#pragma once

#include "Vector/Base.h"
#include "Vector/2.h"
#include "Vector/3.h"
#include "Vector/4.h"
#include "Vector/Generic.h"

namespace Math {
    template <class T, class ...U>
    explicit Vec(T vc, U&& ... val) -> Vec<sizeof...(val) + 1, T>;
}
