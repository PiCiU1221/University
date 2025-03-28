#include <stdio.h>
#include <math.h>
#include <vector>
#include <thread>
#include <iostream>

const int iXmax = 10000;
const int iYmax = 10000;

const double CxMin=-2.5;
const double CxMax=1.5;
const double CyMin=-2.0;
const double CyMax=2.0;

const int IterationMax=200;
const double EscapeRadius=2;
double ER2=EscapeRadius*EscapeRadius;

unsigned char colorArray[iYmax][iXmax][3];

double PixelWidth=(CxMax-CxMin)/iXmax;
double PixelHeight=(CyMax-CyMin)/iYmax;

void thread_function(int tid, int num_threads) {
//    auto start_time = std::chrono::high_resolution_clock::now();

    int lb = (iYmax / num_threads) * tid;
    int ub = lb + (iYmax / num_threads) - 1;

    int iX, iY;
    double Cx, Cy;
    double Zx, Zy;
    double Zx2, Zy2;
    int Iteration;
    unsigned char color[3];
    int uniqueThreadColor = 100 / num_threads * tid + 50;

    for(iY=lb; iY<= ub; iY++)
    {
        Cy=CyMin + iY*PixelHeight;
        if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
        for(iX=0;iX<iXmax;iX++)
        {
            Cx=CxMin + iX*PixelWidth;
            /* initial value of orbit = critical point Z= 0 */
            Zx=0.0;
            Zy=0.0;
            Zx2=Zx*Zx;
            Zy2=Zy*Zy;

            for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
            {
                Zy=2*Zx*Zy + Cy;
                Zx=Zx2-Zy2 +Cx;
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;
            }
            /* compute  pixel color (24 bit = 3 bytes) */
            if (Iteration==IterationMax)
            { /*  interior of Mandelbrot set = black */
                color[0]=0;
                color[1]=0;
                color[2]=0;
            }
            else
            { /* exterior of Mandelbrot set = white */

                color[0]=uniqueThreadColor; /* Red*/
                color[1]=128; /* Green */
                color[2]=0; /* Blue */
            };

            colorArray[iY][iX][0] = color[0];
            colorArray[iY][iX][1] = color[1];
            colorArray[iY][iX][2] = color[2];
        }
    }

//    auto end_time = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
//    std::cout << "Thread " << tid << " completed its task in " << duration.count() << " ms" << std::endl;
}

int main(int argc, char* argv[])
{
    int num_threads = atoi(argv[1]);
//    int num_threads = 3;

    const int MaxColorComponentValue=255;
    FILE * fp;
    char *filename="new1.ppm";
    char *comment="# ";/* comment should start with # */

    std::vector<std::thread> th;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++) {
        th.push_back(std::thread(thread_function, i, num_threads));
    }

    for (auto &t : th) {
        t.join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << duration.count() << " ms" << std::endl;

    /*create new file,give it a name and open it in binary mode  */
    fp= fopen(filename,"wb"); /* b -  binary mode */
    /*write ASCII header to the file*/
    fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);

    for(int y = 0; y < iYmax; y++) {
        for (int x = 0; x < iXmax; x++) {
            fwrite(colorArray[y][x],1,3,fp);
        }
    }

    fclose(fp);
    return 0;
}
