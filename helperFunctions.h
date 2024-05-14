#pragma once

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cfloat>

using namespace std;


int findFirstPos(vector<vector<float> > matrix);
int findFirstNeg(vector<vector<float> > matrix);

int findFirstPos(vector<vector<float> > matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][0] > 0) {
            return i;
        }
    }
    return -1;
}

int findFirstNeg(vector<vector<float> > matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][0] < 0) {
            return i;
        }
    }
    return -1;
}

void divideRowByConstant(float** array, int rowNum, int width, float constant) {
    for (int i=0; i<width; i++) {
        array[rowNum][i] = array[rowNum][i] * (1.0/constant);
    }
}

void swapRows(vector<vector<float> >* mat, int row1, int row2, int width) {

    vector<float> temp = (*mat)[row1];
    (*mat)[row1] = (*mat)[row2];
    (*mat)[row2] = temp;
}

void printMat(vector<vector<float> > workMat) {
    for (int i = 0; i < workMat.size(); i++) {
        for (int j = 0; j < workMat[i].size(); j++) {
            cout << " " << workMat[i][j];
        }
        cout << endl;
    }
}
