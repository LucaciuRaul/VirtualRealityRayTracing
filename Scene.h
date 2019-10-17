#include "Geometry.h"
#include "Sphere.h"
#include "Light.h"

using namespace rt;

int geometryCount = 8;
//red 1
//yellow 2
//green 3
//white 4
//small blue 5
//pink 6
//blue 7
//black 8
Geometry* scene[] = {
    ///red
    new Sphere( -50.0f,  -25.0f,  175.0f,   30.0f,
            0.3f,  0.0f,  0.0f,
            0.80f, 0.10f,   0.10f,
            1.0f,  0.10f, 0.10f, 10.0f),
    ///yellow
    new Sphere( -10.0f,    0.0f,  100.0f,   10.0f,
            0.3f,  0.3f,  0.0f,
            0.80f, 0.80f, 0.10f,
            1.0f, 1.0f, 0.10f, 10.0f),
    ///green
    new Sphere(   0.0f,    0.0f,  200.0f,   40.0f,
            0.0f,  0.3f,  0.0f,
            0.10f, 0.80f, 0.10f,
            0.10f, 1.0f, 0.10f, 10.0f),
    ///white
    new Sphere(   0.0f,  -50.0f,  200.0f,   10.0f,
            0.3f,  0.3f,  0.3f,
            0.80f, 0.80f, 0.80f,
            1.0f, 1.0f, 1.0f, 10.0f),
    ///small blue
    new Sphere(  10.0f,    0.0f,   20.0f,    5.0f,
            0.0f,  0.3f,  0.3f,
            0.80f, 0.80f, 0.80f,
            0.10f, 1.0f, 1.0f, 10.0f),
    ///pink
    new Sphere( -70.0f,    0.0f,  100.0f,   10.0f,
            0.3f,  0.0f,  0.3f,
            0.80f, 0.10f, 0.80f,
            1.0f, 0.10f, 1.0f, 10.0f),
    ///blue
    new Sphere(  50.0f,   25.0f,   75.0f,   50.0f,
            0.0f,  0.0f,  0.3f,
            0.10f,   0.10f,   0.80f,
            0.10f, 0.10f, 1.0f, 10.0f),
	///black
    new Sphere( -75.0f,   15.0f,   75.0f,    5.0f,
            0.05f, 0.05f, 0.05f,
            0.50f, 0.50f, 0.50f,
            1.0f, 1.0f, 1.0f, 10.0f)
};

int lightCount = 2;
Light *lights[] = {
        new Light(-50.0f,  0.0f, 0.0f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 1),
        new Light( 20.0f, 20.0f, 0.0f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 1)
};
