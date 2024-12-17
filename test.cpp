#include "vec3.h"
int main(){
  vec3 v(0,1,-1);
  vec3 v2(1,1,2);
  std::cout << v - v2 << '\n';
  std::cout << v * v2 << '\n';
  std::cout << v / v2 << '\n';
  v += v2;


  std::cout << v << '\n';
  std::cout << v2 << '\n';
  std::cout << dot(v,v2)<< '\n';
  std::cout << cross(v,v2)<< '\n';
  
}
