#include <cmath>
#include <iostream>
#include <string>

#include "Vector.h"
#include "Line.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Image.h"
#include "Color.h"
#include "Intersection.h"
#include "Material.h"

#include "Scene.h"

using namespace std;
using namespace rt;

float imageToViewPlane(int n, int imgSize, float viewPlaneSize) {
    float u = (float) n * viewPlaneSize / (float) imgSize;
    u -= viewPlaneSize / 2;
    return u;
}

const Intersection findFirstIntersection(const Line &ray,
                                         float minDist, float maxDist) {
    Intersection intersection;

    for (int i = 0; i < geometryCount; i++) {
        Intersection in = scene[i]->getIntersection(ray, minDist, maxDist);
        if (in.valid()) {
            if (!intersection.valid()) {
                intersection = in;
            } else if (in.t() < intersection.t()) {
                intersection = in;
            }
        }
    }

    return intersection;
}

const Color getMaxColor(Color a, Color b) {
    Color c{max(a.red(), b.red()), max(a.green(), b.green()), max(a.blue(), b.blue())};
    return c;
}

int main() {
    Vector viewPoint(-50, 10, 0);
    Vector viewDirection(50, -10, 100);
    Vector viewUp(0, -1, 0);

    Color BLACK{0, 0, 0};

    viewDirection.normalize();
    viewUp.normalize();

    float frontPlaneDist = 0;
    float backPlaneDist = 1000;

    float viewPlaneDist = 65;
    float viewPlaneWidth = 160;
    float viewPlaneHeight = 120;

//    int imageWidth = 1024;
//    int imageHeight = 768;
    int imageWidth = 320;
    int imageHeight = 240;


    Vector viewParallel = viewUp ^viewDirection;
    viewParallel.normalize();

    Image image(imageWidth, imageHeight);

    // ADD CODE HERE
    for (int k = 0; k < 1; k++) {
        for (int i = 0; i < imageHeight; i++) {
            for (int j = 0; j < imageWidth; j++) {
                Vector pixel = viewPoint + viewDirection * viewPlaneDist +
                               viewUp * imageToViewPlane(i, imageHeight, viewPlaneHeight) +
                               viewParallel * imageToViewPlane(j, imageWidth, viewPlaneWidth);

                Intersection intersect = findFirstIntersection(Line(viewPoint, pixel, false),
                                                               frontPlaneDist, backPlaneDist);

                if (intersect.valid()) {
                    Vector N{intersect.geometry()->normal(intersect.vec())};
                    N.normalize();

                    Line geometry_to_camera{intersect.vec(), viewPoint, false};
                    Vector E{geometry_to_camera.dx()};
                    E.normalize();


                    Line inverse_light_line{intersect.vec(), lights[0]->position(), false};
                    Vector T{inverse_light_line.dx()};
                    T.normalize();

                    Vector R{(N * (N * T) * 2) - T};
                    R.normalize();

                    Color color_with_lighting{intersect.geometry()->material().ambient() * lights[0]->ambient()};
                    if (N * T > 0) {
                        color_with_lighting +=
                                intersect.geometry()->material().diffuse() * lights[0]->diffuse() * (N * T);
                    }
                    if (E * R > 0) {
                        color_with_lighting += intersect.geometry()->material().specular() * lights[0]->specular() *
                                               pow(E * R, intersect.geometry()->material().shininess());
                    }
                    color_with_lighting *= (float) lights[0]->intensity();


                    Line inverse_light_line2{intersect.vec(), lights[1]->position(), false};
                    Vector T2{inverse_light_line2.dx()};
                    T2.normalize();

                    Vector R2{(N * (N * T2) * 2) - T2};
                    R2.normalize();

                    Color color_with_lighting2{intersect.geometry()->material().ambient() * lights[1]->ambient()};
                    if (N * T2 > 0) {
                        color_with_lighting2 +=
                                intersect.geometry()->material().diffuse() * lights[1]->diffuse() * (N * T2);
                    }
                    if (E * R2 > 0) {
                        color_with_lighting2 += intersect.geometry()->material().specular() * lights[1]->specular() *
                                                pow(E * R2, intersect.geometry()->material().shininess());
                    }
                    color_with_lighting2 *= (float) lights[1]->intensity();

                    image.setPixel(j, i, color_with_lighting * color_with_lighting2);
                } else {
                    image.setPixel(j, i, BLACK);
                }
            }

            // END OF CODE ADDITION
            image.store("scene" + to_string(k) + ".png");
        }
    }
    for (int i = 0; i < geometryCount; i++) {
        delete scene[i];
    }

    for (int i = 0; i < lightCount; i++) {
        delete lights[i];
    }

    return 0;
}
