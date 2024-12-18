#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include<iostream>
#include <string>
#include <strstream>
#include <vector>
#include <fstream>
#include "vec3.h"
using color = vec3;
using point3 = vec3;
void write_color(std::ostream& out, const color& pixel_color){
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();
  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);
  out << rbyte << " " << gbyte << " " << bbyte << '\n';
}




int main(){
  int image_width = 256;
  int max_value = 255;
  /*std::cin >> image_width;*/
  double w_r_h = 16.0/9.0;
  /*std::cout << w_r_h <<std::endl;*/

  int image_height = ((double)image_width / w_r_h);
  image_height = image_height == 0 ? 1 : image_height;
  /*std::cout << image_height;*/
/*int image_height = 100;*/
  point3 camera(0,0,0);
  int pix_dis = 2;//how accurate the picture is
  point3 canvas_center(0,0,2);
  double focal = 1.0;

  double viewport_width = 4.0;
  //The viewport is a virtual rectangle in the 3D world that contains the grid of image pixel locations.
  double viewport_height = viewport_width * ((double)image_height/(double)image_width);
  vec3 delta_v_h((viewport_width/(double)image_width), 0, 0);
  vec3 delta_v_v(0, viewport_height/(double)image_height, 0);
  point3 viewport_00_loc = camera + vec3(- viewport_width*0.5,- viewport_height*0.5,focal) + 0.5*(delta_v_v + delta_v_h); 
 /* std::cout << "vv " << delta_v_v << '\n';*/
 /* std::cout << "vv " << */
 /*vec3(- viewport_width*0.5,- viewport_height*0.5,focal)*/
 /*<< '\n';*/
 /* std::cout << "00loc " << viewport_00_loc << '\n';*/
 /**/
  std::string filename = "image2.ppm";
  std::fstream fstr;
  fstr.open(filename, std::ios::in | std::ios::out);
  assert(fstr.is_open());
  fstr << "P3\n" << image_width << " " << image_height << "\n" << max_value << '\n';

  /*std::vector<int> line(image_height);*/
  for(int i=0; i < image_height; i ++)
  {
    for(int j=0; j < image_width; j ++)
    {
      vec3 ray = viewport_00_loc + i * delta_v_v + j * delta_v_h;
      if(i + j < 5) std::cout << ray << '\n';
      point3 sphere_center(0,0,2);
      double r = 0.5;
      double a = dot(ray , ray);
      double b = 2*dot((ray - sphere_center),ray);
      double c = dot((ray - sphere_center),(ray - sphere_center)) - r*r;
      double Delta = b*b - 4*a*c;
      double t = (-b - sqrt(Delta)) / (2 * a);
      vec3 N = (((1+t) * ray) - sphere_center) / r;
      color color_rainbow = 0.5*color(1+N.x(),1+N.y(),1+N.z());
      /*std::cout << Delta << " " ;*/
      double color_blue = abs(ray.y() - viewport_00_loc.y())/viewport_height;
      if(Delta < 0)
        write_color(fstr, color(1, 1, color_blue));
      else 
        write_color(fstr, color_rainbow);
    }
  }
  std::clog << "\rDone";
  fstr.close();
}
