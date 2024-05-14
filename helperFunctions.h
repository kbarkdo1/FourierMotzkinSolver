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

