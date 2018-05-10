//
//  material.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 18/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef material_h
#define material_h
#include "ray.h"




vec3 reflect(const vec3& v, const vec3& n){
    return v - 2 * dot(v, n) * n;
}

vec3 random_in_unit_sphere(){
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(),drand48()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class material {    
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec,vec3& attentuation, ray& scattered) const = 0;
};

#endif /* material_h */
