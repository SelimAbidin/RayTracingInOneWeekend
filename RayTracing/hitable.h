//
//  hittable.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 18/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef hitable_h
#define hitable_h
#include "ray.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
    
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif /* hitable_h */
