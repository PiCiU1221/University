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

    cam.eyep = {0,-26,7};
    cam.lookp = {0,0,0};
    cam.up = {0,1,0};
    cam.fov = 50 * 3.14f / 180.0f;
    cam.width = 500;
    cam.height = 400;

    CLight light1(glm::vec3(-3, -2, 15));
    light1.color = {0.6, 0.6, 0.6};
    lightList.push_back(light1);

    CLight light2(glm::vec3(5, -2, 20));
    light2.color = {0.3, 0.3, 0.3};
    lightList.push_back(light2);

//    int frame = 0;

    //CSphere* ball = new CSphere({8,-2,6}, 1.6);
//    CSphere* ball = new CSphere({coordinates.at(frame).first,-2, coordinates.at(frame).second}, 1.6);
//    ball->matAmbient = {0.1, 0, 0};
//    ball->matDiffuse = {0.6, 0, 0};
//    ball->matSpecular = {0.7, 0.7, 0.7};
//    ball->matShininess = 30;
//    ball->reflectance = 0;
//    ball->isTexture = false;
//    objectList.push_back(ball);

    CTriangle* floor1 = new CTriangle({20, 5, -5}, {-20, 5, -5}, {-20, -10, -5});
    floor1->matAmbient = {0.1, 0.1, 0.1};
    floor1->matDiffuse = {0.4, 0.4, 0.4};
    floor1->matSpecular = {0, 0, 0};
    floor1->matShininess = 0;
    floor1->reflectance = 1;
    floor1->isTexture = false;
    objectList.push_back(floor1);

    CTriangle* floor2 = new CTriangle({20, 5, -5}, {-20, -10, -5}, {10, -10, -5});
    floor2->matAmbient = {0.1, 0.1, 0.1};
    floor2->matDiffuse = {0.4, 0.4, 0.4};
    floor2->matSpecular = {0, 0, 0};
    floor2->matShininess = 0;
    floor2->reflectance = 1;
    floor2->isTexture = false;
    objectList.push_back(floor2);
}
