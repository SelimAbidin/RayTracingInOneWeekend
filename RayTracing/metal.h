//
//  metal.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 18/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef metal_h
#define metal_h

#include "material.h"
#include "vec3.h"


class metal : public material {
    
public:
    metal(const vec3& a, float f) : albedo(a) { if(f < 1) fuzz = f; else fuzz = 1; };
    virtual bool scatter(const ray& r_in, const hit_record& rec,vec3& attentuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attentuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
    vec3 albedo;
    float fuzz;
};


#endif /* metal_h */
