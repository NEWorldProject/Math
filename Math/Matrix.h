#pragma once

#include "Matrix/Base.h"
#include "Matrix/22.h"
#include "Matrix/23.h"
#include "Matrix/24.h"
#include "Matrix/32.h"
#include "Matrix/33.h"
#include "Matrix/34.h"
#include "Matrix/42.h"
#include "Matrix/43.h"
#include "Matrix/44.h"
#include "Matrix/Generic.h"

namespace Math {
    template <class T, int C, class ...U>
    explicit Mat(const Vec<C, T>& vec, U&& ... vs) -> Mat<T, sizeof...(vs)+1, C>;
}
