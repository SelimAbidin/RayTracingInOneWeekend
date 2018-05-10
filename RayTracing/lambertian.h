//
//  lambertian.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 18/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef lambertian_h
#define lambertian_h

#include "material.h"
#include "vec3.h"


class lambertian : public material {
public:
    lambertian(const vec3& a ) : albedo(a) {};
    virtual bool scatter(const ray& r_in, const hit_record& rec,vec3& attentuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attentuation = albedo;
        return true;
    }
    vec3 albedo;
};

#endif /* lambertian_h */
