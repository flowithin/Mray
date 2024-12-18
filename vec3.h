#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <cmath>
#include <strstream>
class vec3{
public:
  double e[3];
  vec3() : e{0,0,0} {}
  vec3(double e0, double e1, double e2) : e{e0,e1,e2}{}
  double x() const {return e[0];}
  double y() const {return e[1];}
  double z() const {return e[2];}
  vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    vec3& operator-=(const vec3 v2) {e[0] -= v2.e[0]; e[1] -= v2.e[1]; e[2] -= v2.e[2]; return *this;}
  vec3& operator+=(const vec3 v2) {e[0] += v2.e[0]; e[1] += v2.e[1]; e[2] += v2.e[2]; return *this;}
  vec3& operator*=(const vec3 v2) {e[0] *= v2.e[0]; e[1] *= v2.e[1]; e[2] *= v2.e[2]; return *this;}
};
  vec3 operator-(const vec3 v1, const vec3 v2) { return vec3(v1.e[0] - v2.x(), v1.e[1] - v2.y() , v2.e[2] - v2.z());}
  vec3 operator+(const vec3 v1, const vec3 v2) { return vec3(v1.e[0] + v2.x(), v1.e[1] + v2.y(), v1.e[2] + v2.z());}
  /*vec3 operator*(const vec3 v1, const vec3 v2) { return vec3(v1.e[0] * v2.x(), v1.e[1] * v2.y(), v1.e[2] * v2.z());}*/
  vec3 operator*(const double scaler, const vec3 v2) { return vec3(scaler * v2.x(), scaler * v2.y(), scaler * v2.z());}
  /*vec3 operator/(const vec3 v1, const vec3 v2) { return vec3(v1.e[0] / v2.x(), v1.e[1] / v2.y(), v1.e[2] / v2.z());}*/
  vec3 operator/(const vec3 v1, const double scaler) { return (1/scaler)*v1;}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

  std::ostream& operator<<(std::ostream& os, const vec3& v2) {return os << v2.e[0] << " " << v2.e[1]  << " " <<  v2.e[2] << '\n';}
#endif
