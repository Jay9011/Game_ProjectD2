#pragma once
#include "Core/MathUtility.h"
#include "Core/Platform.h"

namespace Engine::Math
{
    template <typename T>
    class TVector
    {
        static_assert(is_floating_point_v<T>, "T must be floating point.");

    public:
        union
        {
            struct
            {
                /** Vector의 X 요소 */
                T X;
                /** Vector의 Y 요소 */
                T Y;
                /** Vector의 Z 요소 */
                T Z;
            };
            /** Vector의 X, Y, Z 요소 */
            T XYZ[3];
        };

        //////////////////////////////////////////////////////////////////////////
        /// 정적 변수: 대표적인 단위 벡터
        //////////////////////////////////////////////////////////////////////////
    public:
        /** (0, 0, 0) */
        static const TVector<T> ZeroVector;
        /** (1, 1, 1) */
        static const TVector<T> OneVector;
        /** (1, 0, 0) // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> RightVector;
        /** (-1, 0, 0) // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> LeftVector;
        /** (0, 1, 0) // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> UpVector;
        /** (0, -1, 0) // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> DownVector;
        /** (0, 0, 1) // 시야 방향 // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> ForwardVector;
        /** (0, 0, -1) // 화면 방향 // 언리얼 좌표계와는 조금 다르게 왼손 좌표계 사용 */
        static const TVector<T> BackwardVector;
        /** X축 단위 벡터 (1, 0, 0) */
        static const TVector<T> XAxisVector;
        /** Y축 단위 벡터 (0, 1, 0) */
        static const TVector<T> YAxisVector;
        /** Z축 단위 벡터 (0, 0, 1) */
        static const TVector<T> ZAxisVector;
        /** (0, 0, 0) */
        static inline TVector<T> Zero() { return ZeroVector; }
        /** (1, 1, 1) */
        static inline TVector<T> One() { return OneVector; }
        /** X축 단위 벡터 (1, 0, 0) */
        static inline TVector<T> UnitX() { return XAxisVector; }
        /** Y축 단위 벡터 (0, 1, 0) */
        static inline TVector<T> UnitY() { return YAxisVector; }
        /** Z축 단위 벡터 (0, 0, 1) */
        static inline TVector<T> UnitZ() { return ZAxisVector; }

    public:
        /** 기본 생성자 (0, 0, 0) */
        FORCEINLINE TVector();
        /**
         * @brief 모든 요소를 inFloat으로 초기화
         *
         * @param inFloat 구성 값
         */
        explicit FORCEINLINE TVector(T inFloat);
        /**
         * @brief X, Y, Z 요소를 초기화
         *
         * @param inX X축
         * @param inY Y축
         * @param inZ Z축
         */
        FORCEINLINE TVector(T inX, T inY, T inZ);

        //////////////////////////////////////////////////////////////////////////
        /// 연산자 오버로딩
        //////////////////////////////////////////////////////////////////////////
    public:
        /** 원소별 덧셈 (요소끼리의 덧셈) */
        FORCEINLINE TVector<T> operator+(const TVector<T>& v) const;
        /** 원소별 뺄셈 (요소끼리의 뺄셈) */
        FORCEINLINE TVector<T> operator-(const TVector<T>& v) const;
        /** 원소별 곱 (요소끼리의 곱) */
        FORCEINLINE TVector<T> operator*(const TVector<T>& v) const;
        /** 원소별 나눗셈 (요소끼리의 나눗셈) */
        FORCEINLINE TVector<T> operator/(const TVector<T>& v) const;
        /** 원소별 덧셈 (요소끼리의 덧셈) */
        FORCEINLINE TVector<T> operator+=(const TVector<T>& v);
        /** 원소별 뺄셈 (요소끼리의 뺄셈) */
        FORCEINLINE TVector<T> operator-=(const TVector<T>& v);
        /** 원소별 곱 (요소끼리의 곱) */
        FORCEINLINE TVector<T> operator*=(const TVector<T>& v);
        /** 원소별 나눗셈 (요소끼리의 나눗셈) */
        FORCEINLINE TVector<T> operator/=(const TVector<T>& v);

        /** 벡터의 내적 (Dot) // 언리얼식 내적 */
        FORCEINLINE T operator|(const TVector<T>& v) const;
        /** 벡터의 내적 (Dot) */
        FORCEINLINE T Dot(const TVector<T>& v) const;
        /**
         * @brief 벡터끼리의 내적(Dot)
         *
         * @param v1 첫 번째 벡터
         * @param v2 두 번째 벡터
         * @return 내적 결과 (스칼라 값)
         */
        FORCEINLINE T DotProduct(const TVector<T>& v1, const TVector<T>& v2);

        /** 벡터의 외적 (Cross) // 언리얼식 외적 */
        FORCEINLINE TVector<T> operator^(const TVector<T>& v) const;
        /** 벡터의 외적 (Cross) */
        FORCEINLINE TVector<T> Cross(const TVector<T>& v) const;
        /**
         * @brief 벡터끼리의 외적(Cross)
         * 
         * @param v1 첫 번째 벡터
         * @param v2 두 번째 벡터
         * @return 외적 결과
         */
        FORCEINLINE static TVector<T> CrossProduct(const TVector<T>& v1, const TVector<T>& v2);

        /** 두 벡터가 같은지 확인 */
        FORCEINLINE bool operator==(const TVector<T>& v) const;
        /** 두 벡터가 다른지 확인 */
        FORCEINLINE bool operator!=(const TVector<T>& v) const;
        /**
         * @brief 오차 범위 내에서 두 벡터가 같은지 확인
         *
         * @param v 비교 벡터
         * @param tolerance 허용치(오차)
         * @return 오차 범위 내에서 같다고 판단되면 true 반환
         */
        FORCEINLINE bool Equals(const TVector<T>& v, T tolerance = KINDA_SMALL_NUMBER) const;
        /** 부호 반전 */
        FORCEINLINE TVector<T> operator-() const;

    //////////////////////////////////////////////////////////////////////////
    /// 유틸리티 함수
    //////////////////////////////////////////////////////////////////////////
    public:
        /**
         * @brief 벡터의 구성 요소 설정
         *
         * @param inX X축
         * @param inY Y축
         * @param inZ Z축
         */
        FORCEINLINE void Set(T inX, T inY, T inZ);
        /** @return 세 요소 중 최댓값을 반환 */
        FORCEINLINE T GetMax() const;
        /** @return 세 요소의 절대값 중 최댓값을 반환 */
        FORCEINLINE T GetAbsMax() const;
        /** @return 세 요소 중 최솟값을 반환 */
        FORCEINLINE T GetMin() const;
        /** @return 세 요소의 절대값 중 최소값을 반환 */
        FORCEINLINE T GetAbsMin() const;
        /** @return 절댓값 벡터(|X|, |Y|, |Z|)를 반환 */
        FORCEINLINE TVector<T> GetAbs() const;
        /** @return 벡터의 3D 길이 */
        FORCEINLINE T Size() const;
        /** @result 벡터의 3D 길이 */
        FORCEINLINE T Length() const;
        /** @result 벡터 3D 길이의 제곱 */
        FORCEINLINE T SizeSquared() const;
        /** @result 벡터 3D 길이의 제곱 */
        FORCEINLINE T SquaredLength() const;
        /** @result 2D 길이 (Z 무시, XY 평면) */
        FORCEINLINE T Size2D() const;
        /** @result 2D 길이의 제곱 (Z 무시, XY 평면) */
        FORCEINLINE T SizeSquared2D() const;
        /**
         * @brief 벡터가 제로 벡터인지 확인
         *
         * @param tolerance 허용 범위(오차 범위)
         * @return 오차 범위 내에서 제로 벡터로 판단되면 true
         */
        FORCEINLINE bool IsNearlyZero(T tolerance = KINDA_SMALL_NUMBER) const;
        /**
         * @brief 벡터가 제로 벡터인지 확인
         *
         * @return 완전한 제로 벡터로 판단되면 true
         */
        FORCEINLINE bool IsZero() const;
        /**
         * @brief 벡터가 단위 벡터(길이가 1.0)인지 확인
         *
         * @param lengthSquaredTolerance 길이^2과 단위벡터(1.0) 차이 허용 범위
         * @return 오차 범위 내에서 단위 벡터로 판단되면 true
         */
        FORCEINLINE bool IsUnit(T lengthSquaredTolerance = KINDA_SMALL_NUMBER) const;
        /**
         * @brief 벡터가 정규화(길이가 1.0) 된 벡터인지 확인
         *
         * @return 정규화 된 벡터라면 true
         */
        FORCEINLINE bool IsNormalized() const;
        /**
         * @brief 자기 자신을 정규화(길이 1.0). 길이가 0인 경우 false 반환 됨
         *
         * @param tolerance 허용 범위(오차 범위)
         * @return 정규화를 성공하면 true
         */
        bool Normalize(T tolerance = SMALL_NUMBER);
        /**
         * @brief 안전하지 않은 정규화 반환. (길이가 0이어도 체크 안함)
         *
         * @return 정규화된 벡터 반환
         */
        FORCEINLINE TVector<T> GetUnsafeNormal() const;
        /**
         * @brief 2D 전용 안전하지 않은 정규화 반환. (길이가 0이어도 체크 안함)
         *
         * @return Z를 무시한 정규화된 벡터 반환
         */
        FORCEINLINE TVector<T> GetUnsafeNormal2D() const;
        /**
         * @brief 안전한 정규화 반환. (길이가 오차범위보다 작은 경우 resultIfZero 반환)
         *
         * @param tolerance 허용 범위(오차 범위)
         * @param resultIfZero 제로 벡터의 경우 반환되는 벡터
         * @return 정규화 된 벡터 반환
         */
        TVector<T> GetSafeNormal(T tolerance = SMALL_NUMBER, const TVector<T>& resultIfZero = ZeroVector) const;
        /**
         * @brief 2D 전용 안전한 정규화 반환. (길이가 오차범위보다 작은 경우 resultIfZero 반환)
         *
         * @param tolerance 허용 범위(오차 범위)
         * @param resultIfZero 제로 벡터의 경우 반환되는 벡터
         * @return Z를 무시한 정규화된 벡터 반환
         */
        TVector<T> GetSafeNormal2D(T tolerance = SMALL_NUMBER, const TVector<T>& resultIfZero = ZeroVector) const;
        /**
         * @brief 벡터의 범위를 Min과 Max 사이로 클램프
         *
         * @param min 최솟값
         * @param max 최댓값
         * @return 클램프 된 벡터
         */
        TVector<T> GetClampedToSize(T min, T max) const;
        /**
         * @brief 2D 벡터의 범위를 Min과 Max 사이로 클램프 (Z 무시)
         *
         * @param min 최솟값
         * @param max 최댓값
         * @return 클램프 된 벡터
         */
        TVector<T> GetClampedToSize2D(T min, T max) const;
        /**
         * @brief 벡터의 최대 범위를 Max로 클램프
         *
         * @param maxSize 최댓값
         * @return 클램프 된 벡터
         */
        TVector<T> GetClampedToMaxSize(T maxSize) const;
        /**
         * @brief 벡터의 최대 범위를 Max로 클램프 (Z 무시)
         *
         * @param maxSize 최댓값
         * @return 클램프 된 벡터
         */
        TVector<T> GetClampedToMaxSize2D(T maxSize) const;

        /**
         * @brief 두 벡터 사이의 유클리드 거리를 측정 (루트 연산 사용)
         *
         * @param v1 첫 번재 벡터
         * @param v2 두 번째 벡터
         * @return 두 벡터 사이의 거리
         */
        static FORCEINLINE T Dist(const TVector<T>& v1, const TVector<T>& v2);
        /**
         * @brief 두 벡터 사이의 유클리드 거리를 측정 (루트 연산 사용)
         *
         * @param v1 첫 번재 벡터
         * @param v2 두 번째 벡터
         * @return 두 벡터 사이의 거리
         */
        static FORCEINLINE T Distance(const TVector<T>& v1, const TVector<T>& v2) { return Dist(v1, v2); }
        /**
         * @brief 두 벡터 사이의 유클리드 거리를 측정 (루트 연산 사용)
         *
         * @param v1 첫 번째 벡터
         * @param v2 두 번재 벡터
         * @return 2D (XY좌표) 거리
         */
        static FORCEINLINE T DistXY(const TVector<T>& v1, const TVector<T>& v2);
        /**
         * @brief 두 벡터 사이의 유클리드 거리를 측정 (루트 연산 사용)
         *
         * @param v1 첫 번째 벡터
         * @param v2 두 번재 벡터
         * @return 2D (XY좌표) 거리
         */
        static FORCEINLINE T Dist2D(const TVector<T>& v1, const TVector<T>& v2) { return DistXY(v1, v2); }
        /**
         * @brief 두 벡터 사이의 유클리드 거리 제곱을 측정
         *
         * @param v1 첫 번재 벡터
         * @param v2 두 번째 벡터
         * @return 두 벡터 사이의 거리 제곱
         */
        static FORCEINLINE T DistSquared(const TVector<T>& v1, const TVector<T>& v2);
        /**
         * @brief 두 벡터 사이의 유클리드 거리 제곱을 측정
         *
         * @param v1 첫 번재 벡터
         * @param v2 두 번째 벡터
         * @return 두 벡터 사이의 2D (XY좌표) 거리 제곱
         */
        static FORCEINLINE T DistSquaredXY(const TVector<T>& v1, const TVector<T>& v2);
        /**
         * @brief 두 벡터 사이의 유클리드 거리 제곱을 측정
         *
         * @param v1 첫 번재 벡터
         * @param v2 두 번째 벡터
         * @return 두 벡터 사이의 2D (XY좌표) 거리 제곱
         */
        static FORCEINLINE T DistSquared2D(const TVector<T>& v1, const TVector<T>& v2) { return DistSquaredXY(v1, v2); }
        /**
         * @brief A와 B 벡터의 x, y, z 각각의 최소값을 반환
         *
         * @param A A 벡터
         * @param B B 벡터
         * @return 두 벡터의 각 요소별 최소값
         */
        static FORCEINLINE TVector<T> Min(const TVector<T>& A, const TVector<T>& B);
        /**
         * @brief A와 B 벡터의 x, y, z 각각의 최대값을 반환
         *
         * @param A A 벡터
         * @param B B 벡터
         * @return 두 벡터의 각 요소별 최대값
         */
        static FORCEINLINE TVector<T> Max(const TVector<T>& A, const TVector<T>& B);

    //////////////////////////////////////////////////////////////////////////
    /// Reflection
    //////////////////////////////////////////////////////////////////////////
    public:
        string ToString() const;
    };

    //////////////////////////////////////////////////////////////////////////
    /// 구현부
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    FORCEINLINE TVector<T>::TVector()
        : X(0), Y(0), Z(0)
    {
    }

    template <typename T>
    FORCEINLINE TVector<T>::TVector(T inFloat)
        : X(inFloat), Y(inFloat), Z(inFloat)
    {
    }

    template <typename T>
    FORCEINLINE TVector<T>::TVector(T inX, T inY, T inZ)
        : X(inX), Y(inY), Z(inZ)
    {
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator+(const TVector<T>& v) const
    {
        return TVector<T>(X + v.X, Y + v.Y, Z + v.Z);
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator-(const TVector<T>& v) const
    {
        return TVector<T>(X - v.X, Y - v.Y, Z - v.Z);
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator*(const TVector<T>& v) const
    {
        return TVector<T>(X * v.X, Y * v.Y, Z * v.Z);
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator/(const TVector<T>& v) const
    {
        return TVector<T>(X / v.X, Y / v.Y, Z / v.Z);
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator+=(const TVector<T>& v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator-=(const TVector<T>& v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator*=(const TVector<T>& v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        return *this;
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator/=(const TVector<T>& v)
    {
        X /= v.X;
        Y /= v.Y;
        Z /= v.Z;
        return *this;
    }

    template <typename T>
    FORCEINLINE T TVector<T>::operator|(const TVector<T>& v) const
    {
        return X * v.X + Y * v.Y + Z * v.Z;
    }

    template <typename T>
    FORCEINLINE T TVector<T>::Dot(const TVector<T>& v) const
    {
        return *this | v;
    }

    template <typename T>
    FORCEINLINE T TVector<T>::DotProduct(const TVector<T>& v1, const TVector<T>& v2)
    {
        return v1 | v2;
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::operator^(const TVector<T>& v) const
    {
        return TVector<T>(
            Y * v.Z - Z * v.Y,
            Z * v.X - X * v.Z,
            X * v.Y - Y * v.X
        );
    }

    template <typename T>
    FORCEINLINE TVector<T> TVector<T>::Cross(const TVector<T>& v) const
    {
        return *this ^ v;
    }

    template <typename T>
    TVector<T> TVector<T>::CrossProduct(const TVector<T>& v1, const TVector<T>& v2)
    {
        return v1 ^ v2;
    }

    template <typename T>
    bool TVector<T>::operator==(const TVector<T>& v) const
    {
        return X == v.X && Y == v.Y && Z == v.Z;
    }

    template <typename T>
    bool TVector<T>::operator!=(const TVector<T>& v) const
    {
        return X != v.X || Y != v.Y || Z != v.Z;
    }

    template <typename T>
    bool TVector<T>::Equals(const TVector<T>& v, T tolerance) const
    {
        return fabs(X - v.X) <= tolerance && fabs(Y - v.Y) <= tolerance && fabs(Z - v.Z) <= tolerance;
    }

    template <typename T>
    TVector<T> TVector<T>::operator-() const
    {
        return TVector<T>(-X, -Y, -Z);
    }

    template <typename T>
    void TVector<T>::Set(T inX, T inY, T inZ)
    {
        X = inX;
        Y = inY;
        Z = inZ;
    }

    template <typename T>
    T TVector<T>::GetMax() const
    {
        return fmax(fmax(X, Y), Z);
    }

    template <typename T>
    T TVector<T>::GetAbsMax() const
    {
        return fmax(fmax(fabs(X), fabs(Y)), fabs(Z));
    }

    template <typename T>
    T TVector<T>::GetMin() const
    {
        return fmin(fmin(X, Y), Z);
    }

    template <typename T>
    T TVector<T>::GetAbsMin() const
    {
        return fmin(fmin(fabs(X), fabs(Y)), fabs(Z));
    }

    template <typename T>
    TVector<T> TVector<T>::GetAbs() const
    {
        return TVector<T>(fabs(X), fabs(Y), fabs(Z));
    }

    template <typename T>
    T TVector<T>::Size() const
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    template <typename T>
    T TVector<T>::Length() const
    {
        return Size();
    }

    template <typename T>
    T TVector<T>::SizeSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    template <typename T>
    T TVector<T>::SquaredLength() const
    {
        return SizeSquared();
    }

    template <typename T>
    T TVector<T>::Size2D() const
    {
        return sqrt(X * X + Y * Y);
    }

    template <typename T>
    T TVector<T>::SizeSquared2D() const
    {
        return X * X + Y * Y;
    }

    template <typename T>
    bool TVector<T>::IsNearlyZero(T tolerance) const
    {
        return (fabs(X) <= tolerance)
            && (fabs(Y) <= tolerance)
            && (fabs(Z) <= tolerance);
    }

    template <typename T>
    bool TVector<T>::IsZero() const
    {
        return X == 0.f && Y == 0.f && Z == 0.f;
    }

    template <typename T>
    bool TVector<T>::IsUnit(T lengthSquaredTolerance) const
    {
        return fabs(1.f - SizeSquared()) < lengthSquaredTolerance;
    }

    template <typename T>
    bool TVector<T>::IsNormalized() const
    {
        return fabs(1.f - SizeSquared()) < THRESH_VECTOR_NORMALIZED;
    }

    template <typename T>
    bool TVector<T>::Normalize(T tolerance)
    {
        const T sqrSum = SizeSquared();
        if (sqrSum > tolerance)
        {
            const T scale = (T)1.f / sqrt(sqrSum);
            X *= scale; Y *= scale; Z *= scale;

            return true;
        }
        return false;
    }

    template <typename T>
    TVector<T> TVector<T>::GetUnsafeNormal() const
    {
        const T scale = (T)1.f / Size();
        return TVector<T>(X * scale, Y * scale, Z * scale);
    }

    template <typename T>
    TVector<T> TVector<T>::GetUnsafeNormal2D() const
    {
        const T scale = (T)1.f / Size2D();
        return TVector<T>(X * scale, Y * scale, 0);
    }

    template <typename T>
    TVector<T> TVector<T>::GetSafeNormal(T tolerance, const TVector<T>& resultIfZero) const
    {
        const T squareSum = SizeSquared();

        if (squareSum == 1.f)
        {
            return *this;
        }
        if (squareSum < tolerance)
        {
            return resultIfZero;
        }
        const T scale = (T)1.f / sqrt(squareSum);
        return TVector<T>(X * scale, Y * scale, Z * scale);
    }

    template <typename T>
    TVector<T> TVector<T>::GetSafeNormal2D(T tolerance, const TVector<T>& resultIfZero) const
    {
        const T squareSum = SizeSquared2D();
        if (squareSum == 1.f)
        {
            if (Z == 0.f)
            {
                return *this;
            }
            else
            {
                return TVector<T>(X, Y, 0.f);
            }
        }
        if (squareSum < tolerance)
        {
            return resultIfZero;
        }
        const T scale = (T)1.f / sqrt(squareSum);
        return TVector<T>(X * scale, Y * scale, 0.f);
    }

    template <typename T>
    TVector<T> TVector<T>::GetClampedToSize(T min, T max) const
    {
        T vecSize = Size();
        const TVector<T> vecDir = (vecSize > SMALL_NUMBER) ? *this / vecSize : ZeroVector;

        vecSize = clamp(vecSize, min, max);

        return vecDir * vecSize;
    }

    template <typename T>
    TVector<T> TVector<T>::GetClampedToSize2D(T min, T max) const
    {
        T vecSize = Size2D();
        const TVector<T> vecDir = (vecSize > SMALL_NUMBER) ? (*this/vecSize) : ZeroVector;

        vecSize = clamp(vecSize, min, max);

        return TVector<T>(vecSize * vecDir.X, vecSize * vecDir.Y, Z);
    }

    template <typename T>
    TVector<T> TVector<T>::GetClampedToMaxSize(T maxSize) const
    {
        if (maxSize < KINDA_SMALL_NUMBER)
        {
            return ZeroVector;
        }

        const T vecSq = SizeSquared();
        if (vecSq > Square(maxSize))
        {
            const T scale = maxSize / sqrt(vecSq);
            return TVector<T>(X * scale, Y * scale, Z * scale);
        }
        else
        {
            return *this;
        }
    }

    template <typename T>
    TVector<T> TVector<T>::GetClampedToMaxSize2D(T maxSize) const
    {
        if (maxSize < KINDA_SMALL_NUMBER)
        {
            return TVector<T>(0.f, 0.f, Z);
        }

        const T vecSq2D = SizeSquared2D();
        if (vecSq2D > Square(maxSize))
        {
            const T scale = maxSize / sqrt(vecSq2D);
            return TVector<T>(X * scale, Y * scale, Z);
        }
        else
        {
            return *this;
        }
    }

    template <typename T>
    T TVector<T>::Dist(const TVector<T>& v1, const TVector<T>& v2)
    {
        return sqrt(DistSquared(v1, v2));
    }

    template <typename T>
    T TVector<T>::DistXY(const TVector<T>& v1, const TVector<T>& v2)
    {
        return sqrt(DistSquaredXY(v1, v2));
    }

    template <typename T>
    T TVector<T>::DistSquared(const TVector<T>& v1, const TVector<T>& v2)
    {
        return Square(v2.X - v1.X) + Square(v2.Y - v1.Y) + Square(v2.Z - v1.Z);
    }

    template <typename T>
    T TVector<T>::DistSquaredXY(const TVector<T>& v1, const TVector<T>& v2)
    {
        return Square(v2.X - v1.X) + Square(v2.Y - v1.Y);
    }

    template <typename T>
    TVector<T> TVector<T>::Min(const TVector<T>& A, const TVector<T>& B)
    {
        return TVector<T>(
            fmin(A.X, B.X), 
            fmin(A.Y, B.Y), 
            fmin(A.Z, B.Z)
        );
    }

    template <typename T>
    TVector<T> TVector<T>::Max(const TVector<T>& A, const TVector<T>& B)
    {
        return TVector<T>(
            fmax(A.X, B.X),
            fmax(A.Y, B.Y),
            fmax(A.Z, B.Z)
        );
    }

    template <typename T>
    string TVector<T>::ToString() const
    {
        char buffer[64];
        sprintf_s(buffer, "X=%.3f Y=%.3f Z=%.3f", static_cast<double>(X), static_cast<double>(Y), static_cast<double>(Z));
        return string(buffer);
    }
}
