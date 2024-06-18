
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {

    //draw_triangles();
    //draw_robot();
    //return 0;
    
    std::cout << "ray tracing ... \n";

    CScene scene;
    scene.create(); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }

    CRayTrace rt;
    CRay ray;
    COutput results;

    // CW 15 TEST
//    ray.pos = {0, 0, 0};
//    ray.dir = {0.5f, 0.5f, 0.0f};
//    glm::vec3 n(0, 1.0, 0);
//    glm::vec3 pos = {0, 0, 0};
//    CRay ray_reflected = rt.reflectedRay(ray, n, pos);

//    std::cout << "ray_reflected.pos = [" << ray_reflected.pos[0] << "," << ray_reflected.pos[1] << "," << ray_reflected.pos[2] << std::endl;
//    std::cout << "ray_reflected.dir = [" << ray_reflected.dir[0] << "," << ray_reflected.dir[1] << "," << ray_reflected.dir[2] << std::endl;
    
    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    //std::cout << "Camera projection matrix:" << std::endl;
    //PRINT_MAT3(ray_matrix);

    /// computes ray direction for sample pixel positions
    // TEST 1
    //float fx = scene.cam.width/2-1 + 0.5;
    //float fy = scene.cam.height/2-1 + 0.5;

    // TEST 2
    //float fx = 0.5;
    //float fy = 0.5;

    // TEST 3
    //float fx = scene.cam.width/2-1 + 0.5;
    //float fy = 0.5;

    // TEST 4
    //float fx = 0.5;
    //float fy = scene.cam.height/2-1 + 0.5;

    // TEST 5
//    float fx = scene.cam.width-1 + 0.5;
//    float fy = scene.cam.height-1 + 0.5;

//    ray.pos = scene.cam.eyep;
//    ray.dir = glm::normalize(ray_matrix * glm::vec3(fx,fy,1));
//    std::cout << std::endl << ray.dir[0] << " " << ray.dir[1] << " " << ray.dir[2];

    /// creates raster image object
//    CImage imageX(scene.cam.width, scene.cam.height);
//    CImage imageY(scene.cam.width, scene.cam.height);
//    CImage imageZ(scene.cam.width, scene.cam.height);

    /// main loop
    // TEST
//    ray.pos = {0, 0, 10};
//    ray.dir = {0.3, 0.3, -1};

//    CObject* kula = scene.objectList.back();
//    std::cout << "t: " << kula->intersect(ray) << std::endl;

    ray.pos = scene.cam.eyep;

    CImage image(scene.cam.width, scene.cam.height);

    // Coordinates array
    std::vector<std::pair<double, double>> coordinates = {
            {8.0, 6.0}, {7.67, 5.8}, {7.35, 5.18}, {7.02, 4.16}, {6.69, 2.73},
            {6.37, 0.89}, {6.04, -1.35}, {5.71, -3.4}, {5.39, -3.39}, {5.06, -3.39},
            {4.73, -2.91}, {4.41, -0.7}, {4.08, 1.1}, {3.76, 2.49}, {3.43, 3.47},
            {3.1, 4.05}, {2.78, 4.21}, {2.45, 3.97}, {2.12, 3.32}, {1.8, 2.26},
            {1.47, -2.53}, {1.14, -0.66}, {0.82, 0.81}, {0.49, 1.87}, {0.16, 2.52},
            {-0.16, 2.77}, {-0.49, 2.6}, {-0.82, 2.03}, {-1.14, 1.04}, {-1.47, -0.35},
            {-1.8, -2.26}, {-2.12, -0.69}, {-2.45, 0.47}, {-2.78, 1.23}, {-3.1, 1.57},
            {-3.43, 1.51}, {-3.76, 1.04}, {-4.08, 0.16}, {-4.41, -1.13}, {-4.73, -2.83},
            {-5.06, -2.08}, {-5.39, -0.79}, {-5.71, 0.09}, {-6.04, 0.56}, {-6.37, 0.62},
            {-6.69, 0.27}, {-7.02, -0.48}, {-7.35, -1.65}, {-7.67, -3.22}, {-8.0, 0.0}
    };

    for (int frame = 0; frame < coordinates.size(); ++frame) {
        // Your rendering logic here...

        // Modify the sphere position based on the current frame
        CSphere* ball = new CSphere({coordinates.at(frame).first, -2, coordinates.at(frame).second}, 1.6);
        ball->matAmbient = {0.1, 0, 0};
        ball->matDiffuse = {0.6, 0, 0};
        ball->matSpecular = {0.7, 0.7, 0.7};
        ball->matShininess = 30;
        ball->reflectance = 0;
        ball->isTexture = false;
        scene.objectList.push_back(ball);

        // Render the scene...
        for (int j = 0; j < scene.cam.height; j++) {
            for (int i = 0; i < scene.cam.width; i++) {
                // position of the image point
                float fx = (float)i + 0.5f;
                float fy = (float)j + 0.5f;

                /// background color
                results.col = {0,0,0};
                results.energy = 1.0f;
                results.tree = 0;

                ray.dir = glm::normalize(ray_matrix * glm::vec3(fx,fy,1));

                /// secondary ray counter
                // results.tree = 0;

                /// ray energy
                // results.energy = 1.0f;

                /// rendering
                rt.rayTrace(scene, ray, results);

                /// handles pixel over-saturation
                if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
                    results.col = {1,1,1};
                }

                /// writes pixel to output image
                image.setPixel(i, j, results.col);
            }
        }

        // Save the image with a unique filename for each frame
        std::string filename = "frames/frame_" + std::to_string(frame) + ".png";
        image.save(filename, true);

        // Cleanup for the next frame
        delete ball;
        scene.objectList.pop_back();  // Assuming you always add the ball as the last object
    }

//    image.save("output_image.png", true);

    /// writes image to disk file with gamma correction
//    imageX.save("imageX.png", false);
//    imageY.save("imageY.png", false);
//    imageZ.save("imageZ.png", false);

    //cv::imshow("image", image.getImage());
    //cv::waitKey();
    
    std::cout << std::endl << std::endl;
    return 0;
}


/// Draws two trianges
void draw_triangles() {

    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
//    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}

/// Draws robot.
void draw_robot() {
    CImage img(1000, 1000);

    glm::vec3 color(1,0.6,0);

    // BODY

    // square vertices
    glm::vec3 pp0(-0.5, 0.5, 1);
    glm::vec3 pp1(0.5, 0.5, 1);
    glm::vec3 pp2(0.5, -0.5, 1);
    glm::vec3 pp3(-0.5,-0.5,1);

    // scaling
    float sX = 0.25f; // OX scaling
    float sY = 0.4f; // OY scaling
    glm::mat3x3 sTrans {{sX,0,0}, {0,sY,0}, {0,0,1}}; // scaling matrix

    // scaling of vertices
    pp0 = sTrans * pp0;
    pp1 = sTrans * pp1;
    pp2 = sTrans * pp2;
    pp3 = sTrans * pp3;

    // translation
    float tX = 0.0f; // OX translation
    float tY = 0.2f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

    // HEAD

    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;

    // translation
    tX = 0.0f; // OX translation
    tY = 0.52f; // OY translation
    glm::mat3x3 mTransHead {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    pp = mTransHead * pp;

    img.drawCircle(pp, radius, color);

    // LEFT ARM

    // square vertices
    pp0 = glm::vec3(-0.5, 0.5, 1);
    pp1 = glm::vec3(0.5, 0.5, 1);
    pp2 = glm::vec3(0.5, -0.5, 1);
    pp3 = glm::vec3(-0.5,-0.5,1);

    // scaling
    sX = 0.1f; // OX scaling
    sY = 0.4f; // OY scaling
    sTrans = glm::mat3x3 {{sX,0,0}, {0,sY,0}, {0,0,1}}; // scaling matrix

    // scaling of vertices
    pp0 = sTrans * pp0;
    pp1 = sTrans * pp1;
    pp2 = sTrans * pp2;
    pp3 = sTrans * pp3;

    // rotation
    double r = glm::radians(90.0); // rotation
    glm::mat3x3 rTrans {{cos(r),-sin(r),0},
                        {sin(r),cos(r),0},
                        {0,0,1}}; // rotation matrix

    // rotation of vertices
    pp0 = rTrans * pp0;
    pp1 = rTrans * pp1;
    pp2 = rTrans * pp2;
    pp3 = rTrans * pp3;

    // translation
    tX = 0.35f; // OX translation
    tY = 0.35f; // OY translation
    mTrans = glm::mat3x3 {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

    // RIGHT ARM

    // square vertices
    pp0 = glm::vec3(-0.5, 0.5, 1);
    pp1 = glm::vec3(0.5, 0.5, 1);
    pp2 = glm::vec3(0.5, -0.5, 1);
    pp3 = glm::vec3(-0.5,-0.5,1);

    // scaling
    sX = 0.1f; // OX scaling
    sY = 0.4f; // OY scaling
    sTrans = glm::mat3x3 {{sX,0,0}, {0,sY,0}, {0,0,1}}; // scaling matrix

    // scaling of vertices
    pp0 = sTrans * pp0;
    pp1 = sTrans * pp1;
    pp2 = sTrans * pp2;
    pp3 = sTrans * pp3;

    // rotation
    r = glm::radians(90.0); // rotation
    rTrans  = glm::mat3x3 {{cos(r),-sin(r),0},
                        {sin(r),cos(r),0},
                        {0,0,1}}; // rotation matrix

    // rotation of vertices
    pp0 = rTrans * pp0;
    pp1 = rTrans * pp1;
    pp2 = rTrans * pp2;
    pp3 = rTrans * pp3;

    // translation
    tX = -0.35f; // OX translation
    tY = 0.35f; // OY translation
    mTrans = glm::mat3x3 {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

    // LEFT LEG

    // square vertices
    pp0 = glm::vec3(-0.5, 0.5, 1);
    pp1 = glm::vec3(0.5, 0.5, 1);
    pp2 = glm::vec3(0.5, -0.5, 1);
    pp3 = glm::vec3(-0.5,-0.5,1);

    // scaling
    sX = 0.1f; // OX scaling
    sY = 0.4f; // OY scaling
    sTrans = glm::mat3x3 {{sX,0,0}, {0,sY,0}, {0,0,1}}; // scaling matrix

    // scaling of vertices
    pp0 = sTrans * pp0;
    pp1 = sTrans * pp1;
    pp2 = sTrans * pp2;
    pp3 = sTrans * pp3;

    // rotation
    r = glm::radians(135.0); // rotation
    rTrans  = glm::mat3x3 {{cos(r),-sin(r),0},
                           {sin(r),cos(r),0},
                           {0,0,1}}; // rotation matrix

    // rotation of vertices
    pp0 = rTrans * pp0;
    pp1 = rTrans * pp1;
    pp2 = rTrans * pp2;
    pp3 = rTrans * pp3;

    // translation
    tX = 0.27f; // OX translation
    tY = -0.17f; // OY translation
    mTrans = glm::mat3x3 {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

    // RIGHT LEG

    // square vertices
    pp0 = glm::vec3(-0.5, 0.5, 1);
    pp1 = glm::vec3(0.5, 0.5, 1);
    pp2 = glm::vec3(0.5, -0.5, 1);
    pp3 = glm::vec3(-0.5,-0.5,1);

    // scaling
    sX = 0.1f; // OX scaling
    sY = 0.4f; // OY scaling
    sTrans = glm::mat3x3 {{sX,0,0}, {0,sY,0}, {0,0,1}}; // scaling matrix

    // scaling of vertices
    pp0 = sTrans * pp0;
    pp1 = sTrans * pp1;
    pp2 = sTrans * pp2;
    pp3 = sTrans * pp3;

    // rotation
    r = glm::radians(45.0); // rotation
    rTrans  = glm::mat3x3 {{cos(r),-sin(r),0},
                           {sin(r),cos(r),0},
                           {0,0,1}}; // rotation matrix

    // rotation of vertices
    pp0 = rTrans * pp0;
    pp1 = rTrans * pp1;
    pp2 = rTrans * pp2;
    pp3 = rTrans * pp3;

    // translation
    tX = -0.27f; // OX translation
    tY = -0.17f; // OY translation
    mTrans = glm::mat3x3 {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img.drawLine(pp0, pp1, color);
    img.drawLine(pp1, pp2, color);
    img.drawLine(pp2, pp3, color);
    img.drawLine(pp3, pp0, color);

    // DISPLAY

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}
