// robot-3d.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct robotPosition {
    int r;
    int c;
    int l;
};

//Matrix which resembles the cube the robot will navigate around.
const int r = 5;
const int c = 5;
const int l = 7;
int matrix[r][c][l];
int matrixCopy[r][c][l];

void populateMatrix();
void printMatrixAndRobot(robotPosition robot);


int main()
{
    populateMatrix();

    //Setup the robots initial starting position
    robotPosition robot = {0, rand() % c, rand() % l};

    std::cout << "Starting Position: " << robot.r << " " << robot.c << " " << robot.l << " " << std::endl;
    
    //Start at the top layer and then iterate through each layer (top to bottom) and determine the best move at each layer for the robot
    //Start by looking at layer 1 since the robot already starts on layer 0.
    int overallSum = matrix[robot.r][robot.c][robot.l];
    printMatrixAndRobot(robot);
    for (int i = 1; i < r; i++) {
        robotPosition bestMove = { -1, -1, -1 };
        int highestValue = -1;

        //find the best move based on the robot's current location
        if ((matrix[i][robot.c][robot.l] > highestValue) && (matrixCopy[i][robot.c][robot.l] != -1)) {
            highestValue = matrix[i][robot.c][robot.l];
            bestMove = { i,robot.c,robot.l };
        }

        if (robot.c-1 >= 0) {
            if ((matrix[i][robot.c - 1][robot.l] > highestValue) && (matrixCopy[i][robot.c - 1][robot.l] != -1)) {
                highestValue = matrix[i][robot.c - 1][robot.l];
                bestMove = { i,robot.c - 1, robot.l};
            }
        }
        if (robot.c+1 < c) {
            if ((matrix[i][robot.c + 1][robot.l] > highestValue) && (matrixCopy[i][robot.c + 1][robot.l] != -1)) {
                highestValue = matrix[i][robot.c + 1][robot.l];
                bestMove = { i,robot.c + 1, robot.l };
            }
        }

        if (robot.l - 1 >= 0) {
            if ((matrix[i][robot.c][robot.l - 1] > highestValue) && (matrixCopy[i][robot.c][robot.l - 1] != -1)) {
                highestValue = matrix[i][robot.c][robot.l - 1];
                bestMove = { i,robot.c, robot.l - 1 };
            }
        }
        if (robot.l + 1 < l) {
            if ((matrix[i][robot.c][robot.l + 1] > highestValue) && (matrixCopy[i][robot.c][robot.l + 1] != -1)) {
                highestValue = matrix[i][robot.c][robot.l +1];
                bestMove = { i,robot.c, robot.l + 1};
            }
        }
    
        std::cout << "Next Move Position: " << bestMove.r << " " << bestMove.c << " " << bestMove.l << " MOVE VALUE: " << highestValue << " TOTAL VALUE: " << overallSum << std::endl;
        robot = bestMove;
        overallSum += highestValue;

        //Mark this current position as taken for future iterations
        matrixCopy[bestMove.r][bestMove.c][bestMove.l] = -1;
        printMatrixAndRobot(robot);
    }

    std::cout << "Finishing Position: " << robot.r << " " << robot.c << " " << robot.l << " " << std::endl;
    std::cout << "Overall sum: " << overallSum << std::endl;
}

void populateMatrix() {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < r; i++) {
        std::cout << "LAYER: " << i << " [" << std::endl;
        for (int j = 0; j < c; j++) {
            std::cout << "{";
            for (int k = 0; k < l; k++) {
                matrix[i][j][k] = rand() % 10;
                matrixCopy[i][j][k] = matrix[i][j][k];
                std::cout << matrix[i][j][k] << ",";
            }
            if (j != c - 1) {
                std::cout << "}," << std::endl;
            }
            else { std::cout << "}"; }
            
        }
        if (i != r - 1) {
            std::cout << "]," << std::endl;
        }
        else { std::cout << "]" << std::endl; }
    }
    std::cout << std::endl << std::endl;
}

void printMatrixAndRobot(robotPosition robot) {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < r; i++) {
        if (robot.r == i) {
            std::cout << "LAYER: " << i << " [" << std::endl;
            for (int j = 0; j < c; j++) {
                std::cout << "{";
                for (int k = 0; k < l; k++) {
                    if (robot.r == i && robot.c == j && robot.l == k) {
                        std::cout << "R" << ",";
                    }
                    else {
                        std::cout << matrix[i][j][k] << ",";
                    }
                }
                if (j != c - 1) {
                    std::cout << "}," << std::endl;
                }
                else { std::cout << "}"; }

            }
            if (i != r - 1) {
                std::cout << "]," << std::endl;
            }
            else { std::cout << "]" << std::endl; }
        }
    }
}
