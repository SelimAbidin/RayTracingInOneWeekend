//
//  main.cpp
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 14/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.

#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include <vector>

using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r,rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);
        } else {
            return vec3(0,0,0);
        }
        
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
    }
}




hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                                           new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    
    return new hitable_list(list,i);
}

hitable* orderedScene () {
    
    std::vector<sphere*> spheres;
    
    spheres.push_back(new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(212.0 / 255.0,212.0 / 255.0, 214.0 / 255.0))));
    spheres.push_back(new sphere(vec3(0.0, 5, 0), 5.0, new metal(vec3(0.8, 0.8, 0.8), 0.0)));
    
    
    int dCount = 10;
    float pieceDeg = 360.0 / dCount;
    float pieceRad = pieceDeg / 180 * M_PI;

    float dist = 7;
    float offsetX = 0;
    float offsetZ = 0;
    for (int i = 0; i < dCount; i++) {
        float radyan = pieceRad * i;
        float x = offsetX + cos(radyan) * dist;
        float z = offsetZ + sin(radyan) * dist;
        vec3 pos(x,1,z);
        spheres.push_back(new sphere(pos, 1.0, new dielectric((i * .2)))  );
    }
    
    dist = 10;
    dCount = 20;
    pieceDeg = 360.0 / dCount;
    pieceRad = pieceDeg / 180 * M_PI;
    for (int i = 0; i < dCount; i++) {
        float radyan = pieceRad * i;
        float x = offsetX + cos(radyan) * dist;
        float z = offsetZ + sin(radyan) * dist;
        vec3 pos(x,1,z);
        spheres.push_back(new sphere(pos, 1.0, new lambertian(vec3(drand48(), drand48(), drand48())) ));
    }
    
    
    dist = 13;
    dCount = 21;
    pieceDeg = 360.0 / dCount;
    pieceRad = pieceDeg / 180 * M_PI;
    for (int i = 0; i < dCount; i++) {
        float radyan = pieceRad * i;
        float x = offsetX + cos(radyan) * dist;
        float z = offsetZ + sin(radyan) * dist;
        vec3 pos(x,1,z);
        
        float r = 0.5 + drand48() / 2.0;
        float g = 0.5 + drand48() / 2.0;
        float b = 0.5 + drand48() / 2.0;
        spheres.push_back(new sphere(pos, 1.0, new metal(vec3(r,g,b), drand48())  ));
    }
    
    hitable **list = new hitable*[spheres.size()];
    
    for (int i =0; i < spheres.size(); i++) {
        list[i] = spheres[i];
    }
    
    return new hitable_list(list, (int)spheres.size());
}


int main() {
    int nx = 1200;
    int ny = 800;
    int ns = 500;
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *list[5];
    float R = cos(M_PI/4);
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list,5);
    //world = random_scene();
    
    world = orderedScene();
    vec3 lookfrom(0,20,25);
    vec3 lookat(0,0,0);
    float dist_to_focus = 32.0;
    float aperture = 0;
    
    camera cam(lookfrom, lookat, vec3(0,1,0), 50, float(nx)/float(ny), aperture, dist_to_focus);
    
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world,0);
            }
            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}



//
//
//int main(int argc, const char * argv[]) {
//
//    int nx = 200;
//    int ny = 100;
//    int ns = 300;
//    cout << "P3\n" << nx << " " << ny << "\n255\n";
//
//    hitable *list[5];
//    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.6, 0.2, 0.5)));
//    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
//    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
//    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
//    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
//
//    hitable *world = new hitable_list(list, 5);
//    vec3 lookfrom(3,3,2);
//    vec3 lookat(0,0,-1);
//    float dist_to_focus = (lookfrom - lookat).length();
//    float aperture = 2.0;
//
//    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx) / float(ny),aperture, dist_to_focus);
//    for (int j = ny-1; j >= 0; j--) {
//        for (int i = 0; i < nx; i++) {
//            vec3 col(0,0,0);
//            for (int s = 0; s < ns; s++) {
//                float u =float (i + drand48()) / float(nx);
//                float v = float(j + drand48()) / float(ny);
//                ray r = cam.get_ray(u, v);
//                vec3 p = r.point_at_parameter(2.0);
//                col += color(r, world, 0);
//            }
//            col /= float(ns);
//            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]) );
//            int ir = int(255.99 * col[0]);
//            int ig = int(255.99 * col[1]);
//            int ib = int(255.99 * col[2]);
//
//            cout << ir << " " << ig << " " << ib << "\n";
//        }
//    }
//
//    return 0;
//}

