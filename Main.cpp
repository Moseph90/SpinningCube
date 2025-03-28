#define WIDTH 160
#define HEIGHT 44

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

float A, B, C;
float x, y, z;
float ooz;
int xp, yp;
int indx;
float K1{40};

float cubeWidth{20};
float zBuffer[WIDTH * HEIGHT];
char buffer[WIDTH * HEIGHT];
char backgroundASCIICode{' '};
int distanceFromCamera{100};

float incrementSpeed{1};

//This is how we calculate the X rotation matrix
float calculateX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C)
    + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}
//This is how we calculate the Y rotation matrix
float calculateY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B)
    * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

//This is how we calculate the Z rotation matrix
float calculateZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCamera;

    ooz = 1/z;
    
    //Uncomment the line below and comment the line below that to move the cube to the left
    //xp = (int)(WIDTH/2 - 2 * cubeWidth + K1 * ooz * x * 2);
    xp = (int)(WIDTH/2 + K1 * ooz * x * 2);
    yp = (int)(HEIGHT/2 + K1 * ooz * y);

    indx = xp + yp * WIDTH;
    if (indx >= 0 && indx < WIDTH * HEIGHT) {
        if (ooz > zBuffer[indx]) {
            zBuffer[indx] = ooz;
            buffer[indx] = ch;
        }
    }
}

void delay() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

int main () {
    std::cout << "\x1b[2J";

    //Set the cube area with empty spaces and reserve it for the cube
    while(1) {
        std::fill(std::begin(buffer), std::end(buffer), backgroundASCIICode);
        std::fill(std::begin(zBuffer), std::end(zBuffer), 0.0f);

        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '.');
                calculateForSurface(cubeWidth, cubeY, cubeX, '-');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, 'o');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '~');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, '*'); 
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }
        
        for (int i = 0; i < WIDTH * HEIGHT; i++)
            std::cout << (i % WIDTH ? buffer[i] : '\n');

        std::cout << "\x1b[H";

        A += 0.005;
        B += 0.005;

        //delay();
    }
    return 0;
}
