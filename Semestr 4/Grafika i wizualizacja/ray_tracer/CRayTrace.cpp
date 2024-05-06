//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    glm::vec3 look = cam.lookp - cam.eyep;

    glm::vec3 u = (glm::cross(cam.up,look))/(glm::length(glm::cross(cam.up,look)));

    glm::vec3 v = (glm::cross(u,look))/(glm::length(glm::cross(u,look)));

    glm::vec3 o = (look / glm::length(look))
                  * (cam.width / (2 * tan(cam.fov / 2)))
                  - (((cam.width / 2.0f) * u) + ((cam.height / 2.0f) * v));

    m = {u, v, o};

    return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {
    float tmin = FLT_MAX;
    double EPS = 0.0001;
    CObject* hit_obj = nullptr;

    int MAX_RAY_TREE = 1;
    float MIN_RAY_ENERGY = 0.01;

    for(CObject* obj : scene.objectList) {
        float t = obj->intersect(ray);

        if (t > EPS && t < tmin) {
            tmin = t;
            hit_obj = obj;
        }
    }

    // No intersection
    if (hit_obj == nullptr) {
        return false;
    }

    glm::vec3 p = ray.pos + tmin * ray.dir;
    glm::vec3 n = hit_obj->normal(p);

    for (CLight light : scene.lightList) {
        out.col = out.col + out.energy * light.color * hit_obj->matAmbient;

        glm::vec3 L = glm::normalize(light.pos - p);

        CRay shadow_ray;
        shadow_ray.pos = p;
        shadow_ray.dir = L;

        bool is_shadow = false;

        for (CObject* objShadow : scene.objectList) {
            float tShadow = objShadow->intersect(shadow_ray);
            if (tShadow > EPS) {
                is_shadow = true;
                break;
            }
        }

        if (is_shadow) {
            continue;
        }

        float cos_angle = glm::dot(n, L);

        if (cos_angle > 0.001) {
            out.col = out.col + out.energy * light.color * hit_obj->matDiffuse * cos_angle;

            glm::vec3 V = -ray.dir;
            glm::vec3 h = glm::normalize(L + V);

            float cos_beta = glm::dot(n, h);

            if (cos_beta > 0.001) {
                out.col = out.col + out.energy * light.color * hit_obj->matSpecular * pow(cos_beta, hit_obj->matShininess);
            }
        }
    }

    if (hit_obj->reflectance > 0 && out.tree < MAX_RAY_TREE && out.energy > MIN_RAY_ENERGY) {
        out.tree++;
        out.energy = out.energy * hit_obj->reflectance;
        CRay secondary_ray = reflectedRay(ray, n, p);
        rayTrace(scene, secondary_ray, out);
    }

    if (hit_obj->isTexture) {
        glm::vec2 uv = hit_obj->textureMapping(n);
        glm::vec3 tex_col = CImage::getTexel(hit_obj->texture, uv.x, uv.y);
        out.col = out.col * tex_col;
    }

    /// looks for the closest object along the ray path
    /// returns false if there are no intersection

    /// computes 3D position of the intersection point

    /// computes normal vector at intersection point

    /// for each light source defined in the scene

    /// computes if the intersection point is in the shadows

    /// computes diffuse color component

    /// computes specular color component

    /// adds texture for textured spheres

    /// computes ambient color component

    /// if the surface is reflective

    /// if out.tree >= MAX_RAY_TREE return from function

    /// computes the secondary ray parameters (reflected ray)

    /// recursion
    //   rayTrace(scene, secondary_ray, out);


    return true;
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;

    glm::vec3 v = ray.dir;
    glm::vec3 r = v - (2.0f * glm::dot(v, n)) * n;

    reflected_ray.pos = pos;
    reflected_ray.dir = glm::normalize(r);

    return reflected_ray;
}

