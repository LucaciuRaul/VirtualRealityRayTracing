#include "Sphere.h"

using namespace rt;

Intersection Sphere::getIntersection(const Line& line, float minDist, float maxDist) {
    Intersection in;

    Vector dx = line.dx();
    Vector x0 = line.x0();

    float A = dx * dx;
    float B = 2 * (dx * (x0 - _center));
    float C = (x0 - _center) * (x0 - _center);

    float delta = B*B - 4 * A * (C - _radius * _radius);

    if( delta < 0) {
        return Intersection{};
    }
    else
    {
        float x1 = (-B - sqrt(delta)) / (2 * A);
        float x2 = (-B + sqrt(delta)) / (2 * A);

        if(x1 == x2) {
            if(minDist < x1 && x1 < maxDist)
                return Intersection{true, this, &line, x1};
        }
        if(x1 < x2)
        {
            if(minDist < x1 && x1 < maxDist)
            {
                return Intersection{true, this, &line, x1};
            }
            return Intersection{};
        }
        else{
            if(minDist < x2 && x2 < maxDist)
            {
                return Intersection{true, this, &line, x2};
            }
            return Intersection{};
        }
    }

}


const Vector Sphere::normal(const Vector& vec) const {
    Vector n = vec - _center;
    n.normalize();
    return n;
}