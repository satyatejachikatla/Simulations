#ifndef _CUDA_VECTOR_OPERATIONS_H_VEC2_
#define _CUDA_VECTOR_OPERATIONS_H_VEC2_

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec2  {


public:
	__host__ __device__ vec2() {}
	__host__ __device__ vec2(float e0, float e1) { e[0] = e0; e[1] = e1; }

	__host__ __device__ inline float x() const { return e[0]; }
	__host__ __device__ inline float y() const { return e[1]; }

	__host__ __device__ inline const vec2& operator+() const { return *this; }
	__host__ __device__ inline vec2 operator-() const { return vec2(-e[0], -e[1]); }

	__host__ __device__ inline float operator[](int i) const { return e[i]; }
	__host__ __device__ inline float& operator[](int i) { return e[i]; };

	__host__ __device__ inline vec2& operator+=(const vec2 &v2);
	__host__ __device__ inline vec2& operator-=(const vec2 &v2);
	__host__ __device__ inline vec2& operator*=(const vec2 &v2);
	__host__ __device__ inline vec2& operator/=(const vec2 &v2);
	__host__ __device__ inline vec2& operator*=(const float t);
	__host__ __device__ inline vec2& operator/=(const float t);


	__host__ __device__ inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1]); }
	__host__ __device__ inline float squared_length() const { return e[0]*e[0] + e[1]*e[1]; }
	__host__ __device__ inline void make_unit_vector();

	float e[2];

};

inline std::istream& operator>>(std::istream &is, vec2 &t) {
    is >> t.e[0] >> t.e[1];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec2 &t) {
    os << t.e[0] << " " << t.e[1];
    return os;
}

__host__ __device__ inline void vec2::make_unit_vector() {
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1]);
    e[0] *= k; e[1] *= k;
}

__host__ __device__ inline vec2 operator+(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

__host__ __device__ inline vec2 operator-(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

__host__ __device__ inline vec2 operator*(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}

__host__ __device__ inline vec2 operator/(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}

__host__ __device__ inline vec2 operator*(float t, const vec2 &v) {
    return vec2(t*v.e[0], t*v.e[1]);
}

__host__ __device__ inline vec2 operator/(vec2 v, float t) {
    return vec2(v.e[0]/t, v.e[1]/t);
}

__host__ __device__ inline vec2 operator*(const vec2 &v, float t) {
    return vec2(t*v.e[0], t*v.e[1]);
}

__host__ __device__ inline float dot(const vec2 &v1, const vec2 &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1];
}

__host__ __device__ inline float cross(const vec2 &v1, const vec2 &v2) {
    return v1.e[0]*v2.e[1] - v2.e[0]*v1.e[1];
}


__host__ __device__ inline vec2& vec2::operator+=(const vec2 &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    return *this;
}

__host__ __device__ inline vec2& vec2::operator*=(const vec2 &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    return *this;
}

__host__ __device__ inline vec2& vec2::operator/=(const vec2 &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    return *this;
}

__host__ __device__ inline vec2& vec2::operator-=(const vec2& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    return *this;
}

__host__ __device__ inline vec2& vec2::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    return *this;
}

__host__ __device__ inline vec2& vec2::operator/=(const float t) {
    float k = 1.0/t;

    e[0]  *= k;
    e[1]  *= k;
    return *this;
}

__host__ __device__ inline vec2 unit_vector(vec2 v) {
    return v / v.length();
}

#endif /* _CUDA_VECTOR_OPERATIONS_H_VEC2_ */