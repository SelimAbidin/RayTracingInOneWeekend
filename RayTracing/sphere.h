//
//  sphere.h
//  RayTracingAtWeeknd_1
//
//  Created by YAVUZ SELİM ABIDIN on 18/04/2018.
//  Copyright © 2018 Selim Abidin. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hitable_list.h"
#include "material.h"
class sphere: public hitable {
    
public:
    sphere() {}
    sphere(vec3 cen, float r, material* mat): center(cen), radius(r), material(mat) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 center;
    float radius;
    material* material;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    
    if(discriminant > 0) {
        
        float temp = (-b -sqrt(b*b-a*c)) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
        
        temp = (-b + sqrt(b*b-a*c)) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    
    return false;
}


#endif /* sphere_h */
