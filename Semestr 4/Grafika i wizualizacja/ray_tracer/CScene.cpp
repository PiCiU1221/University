//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create() {

    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects

//    cam.eyep = {0,0,10};
//    cam.lookp = {0,0,0};
//    cam.up = {0,1,0};
//    cam.fov = 50;
//    cam.height = 400;

    // CW. 4 TEST 1
//    cam.eyep = {0,0,10};
//    cam.lookp = {0,0,0};
//    cam.up = {0,1,0};
//    cam.fov = 50 * 3.14f / 180.0f;
//    cam.width = 500;
//    cam.height = 400;

    // CW. 4 TEST 2
//    cam.eyep = {2,5,10};
//    cam.lookp = {-2,1,0};
//    cam.up = {0,1,0};
//    cam.fov = 50 * 3.14f / 180.0f;
//    cam.width = 500;
//    cam.height = 400;

    // CW. 5
//    cam.eyep = {0,0,10};
//    cam.lookp = {0,0,0};
//    cam.up = {0,1,0};
//    cam.fov = 50 * 3.14f / 180.0f;
//    cam.width = 500;
//    cam.height = 400;

//    CSphere* sphere1 = new CSphere({-2.5, 1.3, -3}, 1.0);
//    objectList.push_back(sphere1);
//
//    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
//    objectList.push_back(sphere2);

//    CSphere* sphere1 = new CSphere({-2.5, 1.3, -3}, 1.0);
//    objectList.push_back(sphere1);
//
//    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
//    objectList.push_back(sphere2);

//    CTriangle* triangle = new CTriangle({3, 3, -5}, {-3, 3, -10}, {-3, -3, -8});
//    objectList.push_back(triangle);


    // 1.3 (ambient)
//    CSphere* sphere1 = new CSphere({0, 0, 0}, 1.6);
//    sphere1->matAmbient = {0.5, 0, 0};
//    sphere1->matDiffuse = {0, 0, 0};
//    sphere1->matSpecular = {0, 0, 0};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = false;
//    objectList.push_back(sphere1);

    // 1.4 (diffuse)
//    CSphere* sphere1 = new CSphere({0, 0, 0}, 1.6);
//    sphere1->matAmbient = {0, 0, 0};
//    sphere1->matDiffuse = {0.7, 0, 0};
//    sphere1->matSpecular = {0, 0, 0};
//    sphere1->matShininess = 0;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = false;
//    objectList.push_back(sphere1);

    // 1.5 (specular)
//    CSphere* sphere1 = new CSphere({0, 0, 0}, 1.6);
//    sphere1->matAmbient = {0, 0, 0};
//    sphere1->matDiffuse = {0, 0, 0};
//    sphere1->matSpecular = {0.7, 0.7, 0.7};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = false;
//    objectList.push_back(sphere1);

    // Texture
//    CSphere* sphere1 = new CSphere({0, 0, 0}, 1.6);
//    sphere1->matAmbient = {0.1, 0, 0};
//    sphere1->matDiffuse = {0.6, 0, 0};
//    sphere1->matSpecular = {0.7, 0.7, 0.7};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = true;
//    sphere1->texture = CImage::createTexture(400, 400);
//    objectList.push_back(sphere1);

    // Shadows
//    CSphere* sphere1 = new CSphere({-1, 0, 3}, 0.4);
//    sphere1->matAmbient = {0, 0.1, 0};
//    sphere1->matDiffuse = {0, 0.6, 0};
//    sphere1->matSpecular = {0.7, 0.7, 0.7};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = false;
//    objectList.push_back(sphere1);
//
//    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
//    sphere2->matAmbient = {0.1, 0, 0};
//    sphere2->matDiffuse = {0.6, 0, 0};
//    sphere2->matSpecular = {0.7, 0.7, 0.7};
//    sphere2->matShininess = 30;
//    sphere2->reflectance = 0;
//    sphere2->isTexture = false;
//    objectList.push_back(sphere2);
//
//    CSphere* sphere3 = new CSphere({-3, -2, -2}, 0.6);
//    sphere3->matAmbient = {0, 0, 0.1};
//    sphere3->matDiffuse = {0, 0, 0.6};
//    sphere3->matSpecular = {0.7, 0.7, 0.7};
//    sphere3->matShininess = 30;
//    sphere3->reflectance = 0;
//    sphere3->isTexture = false;
//    objectList.push_back(sphere3);
//
//    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
//    triangle1->matAmbient = {0.1, 0.1, 0.1};
//    triangle1->matDiffuse = {0.4, 0.4, 0.4};
//    triangle1->matSpecular = {0, 0, 0};
//    triangle1->matShininess = 0;
//    triangle1->reflectance = 0;
//    triangle1->isTexture = false;
//    objectList.push_back(triangle1);
//
//    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
//    triangle2->matAmbient = {0.1, 0.1, 0.1};
//    triangle2->matDiffuse = {0.4, 0.4, 0.4};
//    triangle2->matSpecular = {0, 0, 0};
//    triangle2->matShininess = 0;
//    triangle2->reflectance = 0;
//    triangle2->isTexture = false;
//    objectList.push_back(triangle2);
//
//    CLight light1(glm::vec3(-3, -2, 8));
//    light1.color = {0.6, 0.6, 0.6};
//    lightList.push_back(light1);

    // CW 16 SCENA 1
    cam.eyep = {0,-4,10};
    cam.lookp = {0,0,0};
    cam.up = {0,1,0};
    cam.fov = 50 * 3.14f / 180.0f;
    cam.width = 500;
    cam.height = 400;

//    CLight light1(glm::vec3(-3, -2, 8));
//    light1.color = {0.6, 0.6, 0.6};
//    lightList.push_back(light1);
//
//    CSphere* sphere1 = new CSphere({0, 0, 0}, 1.6);
//    sphere1->matAmbient = {0.1, 0, 0};
//    sphere1->matDiffuse = {0.6, 0, 0};
//    sphere1->matSpecular = {0.7, 0.7, 0.7};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//    sphere1->isTexture = false;
//    objectList.push_back(sphere1);
//
//    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
//    triangle1->matAmbient = {0.1, 0.1, 0.1};
//    triangle1->matDiffuse = {0.4, 0.4, 0.4};
//    triangle1->matSpecular = {0, 0, 0};
//    triangle1->matShininess = 0;
//    triangle1->reflectance = 1;
//    triangle1->isTexture = false;
//    objectList.push_back(triangle1);
//
//    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
//    triangle2->matAmbient = {0.1, 0.1, 0.1};
//    triangle2->matDiffuse = {0.4, 0.4, 0.4};
//    triangle2->matSpecular = {0, 0, 0};
//    triangle2->matShininess = 0;
//    triangle2->reflectance = 1;
//    triangle2->isTexture = false;
//    objectList.push_back(triangle2);

    // CW 16 SCENA 2
    CLight light1(glm::vec3(-3, -2, 8));
    light1.color = {0.6, 0.6, 0.6};
    lightList.push_back(light1);

    CLight light2(glm::vec3(5, -2, 8));
    light2.color = {0.3, 0.3, 0.3};
    lightList.push_back(light2);

    CSphere* sphere1 = new CSphere({-1, 0, 3}, 0.4);
    sphere1->matAmbient = {0, 0.1, 0};
    sphere1->matDiffuse = {0, 0.6, 0};
    sphere1->matSpecular = {0.7, 0.7, 0.7};
    sphere1->matShininess = 30;
    sphere1->reflectance = 0;
    sphere1->isTexture = false;
    objectList.push_back(sphere1);

    CSphere* sphere2 = new CSphere({0,0,0}, 1.6);
    sphere2->matAmbient = {0.1, 0, 0};
    sphere2->matDiffuse = {0.6, 0, 0};
    sphere2->matSpecular = {0.7, 0.7, 0.7};
    sphere2->matShininess = 30;
    sphere2->reflectance = 0;
    sphere2->isTexture = false;
    objectList.push_back(sphere2);

    CSphere* sphere3 = new CSphere({-3, -2, -2}, 0.6);
    sphere3->matAmbient = {0, 0, 0.1};
    sphere3->matDiffuse = {0, 0, 0.6};
    sphere3->matSpecular = {0.7, 0.7, 0.7};
    sphere3->matShininess = 30;
    sphere3->reflectance = 0;
    sphere3->isTexture = false;
    objectList.push_back(sphere3);

    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
    triangle1->matAmbient = {0.1, 0.1, 0.1};
    triangle1->matDiffuse = {0.4, 0.4, 0.4};
    triangle1->matSpecular = {0, 0, 0};
    triangle1->matShininess = 0;
    triangle1->reflectance = 1;
    triangle1->isTexture = false;
    objectList.push_back(triangle1);

    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
    triangle2->matAmbient = {0.1, 0.1, 0.1};
    triangle2->matDiffuse = {0.4, 0.4, 0.4};
    triangle2->matSpecular = {0, 0, 0};
    triangle2->matShininess = 0;
    triangle2->reflectance = 1;
    triangle2->isTexture = false;
    objectList.push_back(triangle2);
}
