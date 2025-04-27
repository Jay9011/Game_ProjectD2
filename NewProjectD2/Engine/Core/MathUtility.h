#pragma once

#define PI                          (3.14159265358979323846f)
#define SMALL_NUMBER                (1.e-8f)
#define KINDA_SMALL_NUMBER          (1.e-4f)
#define BIG_NUMBER                  (3.4e+38f)
#define EULERS_NUMBER               (2.71828182845904523536f)
#define GOLDEN_RATIO                (1.6180339887498948482045868343656381f)

#define THRESH_VECTOR_NORMALIZED    (0.01f)
#define THRESH_QUAT_NORMALIZED      (0.01f)

#include "Platform.h"

namespace Engine::Math
{
    template <typename T> struct TVector;
}

using FVector               = Engine::Math::TVector<double>;

using FVector3d             = Engine::Math::TVector<double>;

using FVector3f             = Engine::Math::TVector<float>;

namespace Engine::Math
{
    template <typename T>
    static constexpr FORCEINLINE T Square(T value)
    {
        return value * value;
    }
}