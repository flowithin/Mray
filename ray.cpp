#include <cassert>
#include <cstdio>
#include<iostream>
#include <string>
#include <strstream>
#include <vector>
#include <fstream>
#include "vec3.h"
using color = vec3;
void write_color(std::ostream& out, const color& pixel_color){
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();
  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);
  out << rbyte << " " << bbyte << " " << gbyte << '\n';
  
}
int main(){
  int image_width = 256;
  int image_height = 256;
  int max_value = 255;
  std::string filename = "image2.ppm";
  std::fstream fstr;
  fstr.open(filename, std::ios::in | std::ios::out);
  assert(fstr.is_open());
  fstr << "P3\n" << max_value << "\n" << image_width << " " << image_height << "\n";
  /*std::vector<int> line(image_height);*/
  for(int i=0; i < image_height; i++)
  {
    for(int j=0; j < image_width; j++)
    {
      write_color(fstr, color(static_cast<double>(i)/static_cast<double>(max_value), static_cast<double>(j)/static_cast<double>(max_value), 0));
    }
  }
  std::clog << "\rDone";
  fstr.close();
}
