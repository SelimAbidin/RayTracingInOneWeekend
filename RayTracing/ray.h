//
//  ray.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 15/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef ray_h
#define ray_h
#include "vec3.h"
class ray {
    
public:
    ray(){}
    ray(const vec3& a, const vec3& b) {A = a; B = b;}
    vec3 origin() const {return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t) const {return A + t*B;}
    vec3 A;
    vec3 B;
};


#endif /* ray_h */
