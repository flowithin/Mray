#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include<iostream>
#include <limits>
#include <string>
#include <strstream>
#include <vector>
#include <fstream>
#include "vec3.h"
#include "rand.h"
#define PI
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

class Ray{
public:
  vec3 dir;
  point3 orig;
  double t;
  color ray_color;
  Ray(vec3& dir, color& color,point3 orig = point3(0,0,0)):dir{dir},t{std::numeric_limits<double>::infinity()},ray_color{color},orig{orig}{}
};
class hittable{
  public:
  virtual bool hit(Ray& ray) = 0;

};
class sphere : public hittable{
  point3 center;
  double r;
  public:
  sphere(const point3 &center, double r):center{center},r{r}{}
  bool hit(Ray &ray) override{
    {
      double a = dot(ray.dir, ray.dir);
      vec3 relative_center = center - ray.orig;
      double b = 2*dot((ray.dir - relative_center),ray.dir);
      double c = dot((ray.dir - relative_center),(ray.dir - relative_center)) - r*r;
      double Delta = b*b - 4*a*c;
      double t = (-b - sqrt(Delta)) / (2 * a);
      vec3 N = (((1+t) * ray.dir) - relative_center) / r;
      if(Delta > 0 && t > -1 && t < ray.t )
      {
        ray.ray_color = 0.5*color(1+N.x(),1+N.y(),1+N.z());
        ray.t = t;
      }
      return Delta > 0 && t > -1;
    }
  }
};
class World : public hittable{
  std::vector<hittable*> world;
  void add(hittable& h){world.push_back(&h);}
  bool hit(Ray &ray)override{
    bool flag=false;
    double tempt = ray.t;
    for(hittable* h : world){
      bool rs = h->hit(ray);
      flag = flag == false ? rs : true;
      if(rs && tempt > ray.t)
      {
        tempt = ray.t;
      } 
    }
    return flag;
  }
  void difuse(Ray &ray){
    bool flag = true;
    while(flag){
      double theta = rand_double(-1, 1);
      vec3 new_dir = ray.dir - vec3(theta,theta,theta);
      flag = hit(ray);
      Ray new_ray(new_dir,ray.ray_color, (1+ray.t)*ray.dir + ray.orig);
    }
  }
  ~World() = default;
};
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
  vec3 delta_v_v(0, -viewport_height/(double)image_height, 0);
  point3 viewport_00_loc = camera + vec3(- viewport_width*0.5, viewport_height*0.5,focal) + 0.5*(delta_v_v + delta_v_h); 
  std::string filename = "image2.ppm";
  std::fstream fstr;
  fstr.open(filename, std::ios::in | std::ios::out);
  assert(fstr.is_open());
  fstr << "P3\n" << image_width << " " << image_height << "\n" << max_value << '\n';

  point3 sphere_center(0,0,2);
  sphere ball(sphere_center,0.5);
  sphere ground(point3(0,-100.5,1), 100);
  for(int i=0; i < image_height; i ++)
  {
    for(int j=0; j < image_width; j ++)
    {
      color sampled_color_combine;
      int sample_num = 10;
      for(int k =0 ; k < sample_num; k++){
        int sample = (int)std::floor(rand_double(-0.5, 0.5));
        /*std::cout << "sample " << sample << " ";*/
        vec3 ray_dir = viewport_00_loc + std::max(0, i + sample) * delta_v_v + std::max(0,j + sample) * delta_v_h;
        /*vec3 ray_dir = viewport_00_loc +  i * delta_v_v + j * delta_v_h;*/
        color color_blue = color(1,1,abs(ray_dir.y() - viewport_00_loc.y())/viewport_height);
        Ray ray(ray_dir, color_blue);
        bool hit_sphere = ball.hit(ray);
        bool hit_ground = ground.hit(ray);
        sampled_color_combine += ray.ray_color;
      }
      write_color(fstr, sampled_color_combine/(double)sample_num);
    }
  }
  std::clog << "\rDone";
  fstr.close();
}
