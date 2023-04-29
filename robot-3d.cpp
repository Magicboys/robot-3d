// robot-3d.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

struct robotPosition {
    int r;
    int c;
    int l;
    int score;
};

//Matrix which resembles the cube the robot will navigate around.
const int r = 5;
const int c = 5;
const int l = 7;
int matrix[r][c][l];
std::list<std::list<robotPosition>> paths;


void populateMatrix();
void printMatrixAndRobot(robotPosition robot);


int main()
{
    populateMatrix();

    for (int startingC = 0; startingC < r; startingC++) {
        for (int startingL = 0; startingL < l; startingL++) {
            robotPosition robot = { 0, 0, 0, 0 };
            robot = { 0, startingC, startingL, matrix[0][startingC][startingL] };
            std::list<robotPosition> localPath;
            localPath.push_back(robot);


            //Start by looking at layer 1 since the robot already starts on layer 0.
            int overallSum = matrix[robot.r][robot.c][robot.l];
            for (int i = 1; i < r; i++) {
                robotPosition bestMove = { -1, -1, -1 , -1};
                int highestValue = -1;

                //find the best move based on the robot's current location
                if (matrix[i][robot.c][robot.l] > highestValue) {
                    highestValue = matrix[i][robot.c][robot.l];
                    bestMove = { i,robot.c,robot.l };
                }

                if (robot.c-1 >= 0) {
                    if (matrix[i][robot.c - 1][robot.l] > highestValue) {
                        highestValue = matrix[i][robot.c - 1][robot.l];
                        bestMove = { i,robot.c - 1, robot.l};
                    }
                }
                if (robot.c+1 < c) {
                    if (matrix[i][robot.c + 1][robot.l] > highestValue) {
                        highestValue = matrix[i][robot.c + 1][robot.l];
                        bestMove = { i,robot.c + 1, robot.l };
                    }
                }

                if (robot.l - 1 >= 0) {
                    if (matrix[i][robot.c][robot.l - 1] > highestValue) {
                        highestValue = matrix[i][robot.c][robot.l - 1];
                        bestMove = { i,robot.c, robot.l - 1 };
                    }
                }
                if (robot.l + 1 < l) {
                    if (matrix[i][robot.c][robot.l + 1] > highestValue) {
                        highestValue = matrix[i][robot.c][robot.l +1];
                        bestMove = { i,robot.c, robot.l + 1};
                    }
                }
    
                robot = bestMove;
                overallSum += highestValue;
                robotPosition robot = { bestMove.r, bestMove.c, bestMove.l, overallSum};
                localPath.push_front(robot);
            }

            paths.push_back(localPath);
            auto l = localPath.begin();
            robotPosition test = *l;
            std::cout << "PATH ENDING POINT: " << test.r << " " << test.c << " " << test.l << " PATH TOTAL: " << test.score << std::endl;   
        }
    }

    std::cout << "===========================================" << std::endl;
    int highestPathScore = 0;
    std::list<robotPosition> bestPath;
    for (auto j = paths.begin(); j != paths.end(); j++) {
        std::list<robotPosition> localPath = *j;
        auto l = localPath.begin();
        robotPosition endingPosition = *l;

        if (endingPosition.score > highestPathScore) {
            bestPath = localPath;
            highestPathScore = endingPosition.score;
            std::cout << "NEW BEST PATH SCORE FOUND: " << highestPathScore << std::endl;
        }
    }

    std::cout << "===========================================" << std::endl;
    std::cout << "The maximum gain path for the robot is:" << std::endl;
    std::cout << "Maximum gain: " << highestPathScore << std::endl;
    std::cout << "Best Path: " << std::endl;
    for (auto j = bestPath.rbegin(); j != bestPath.rend(); j++) {
        robotPosition localPosition = *j;
        std::cout << "      matrix[" << localPosition.r << "][" << localPosition.c << "][" << localPosition.l << "] " << " (Element value of " << matrix[localPosition.r][localPosition.c][localPosition.l] << ")" << std::endl;
    }
}

void populateMatrix() {
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < r; i++) {
        std::cout << "LAYER: " << i << " [" << std::endl;
        for (int j = 0; j < c; j++) {
            std::cout << "{";
            for (int k = 0; k < l; k++) {
                matrix[i][j][k] = (rand() % 10) + 1;
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
