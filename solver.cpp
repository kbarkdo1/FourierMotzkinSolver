#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cfloat>
#include "matrixOperations.h"
#include "helperFunctions.h"

using namespace std;

void readInputs(vector<vector<float> >* initMatrix, vector<vector<float> >* coefMatrix);
pair<float, float> recFM(vector<vector<float> > initMatrix, vector<vector<float> > coefMatrix);
bool solveFM(int width, int height, vector<vector<float> > initMatrix, vector<vector<float> > coefMatrix);
void divideRowByConstant(float** array, int rowNum, int width, float constant);
void swapRows(vector<vector<float> >* mat, int row1, int row2, int width);
// vector<vector<float> > sortWorkMat(vector<vector<float> > workMat, int* pos, int* end);
vector<vector<float> > sortMat(vector<vector<float> > workMat);
vector<vector<float> > normalizeWorkMat(vector<vector<float> > workMat);
vector<vector<float> > combineRows(vector<vector<float> > matrix);
void printMat(vector<vector<float> > workMat);
pair<float, float> calcBounds(vector<vector<float> > matrix);


int main() {

    int w;
    int h;
    vector<vector<float> > initMatrix;
    vector<vector<float> > coefMatrix;

    readInputs(&initMatrix, &coefMatrix);
    h = initMatrix.size();
    w = initMatrix[0].size();

    pair<float, float> resultBounds;
    resultBounds = recFM(initMatrix, coefMatrix);

    if (resultBounds.first < resultBounds.second) {
        cout << "solvable: " << endl;
    } else {
        cout << "unsolvable: " << endl; 
    }

    cout << "result bounds: " << resultBounds.first << " < x < " << resultBounds.second << endl;
    return 0; 
}

void readInputs(vector<vector<float> >* initMatrix, vector<vector<float> >* coefMatrix) {
    int rows, columns;
    cin >> rows;
    cin >> columns;
    for (int i=0; i<rows; i++) {
        vector<float> row;
        for (int j=0; j<columns; j++) {
            if (i==j) {
                row.push_back(1.0);
            } else {
                row.push_back(0.0);
            }
        }
        (*coefMatrix).push_back(row);
    }

    for (int j=0; j<rows; j++) {
        vector<float> row;
        for (int i=0; i<columns; i++) {
                float temp;
                cin >> temp;
                row.push_back(temp);
            }
        (*initMatrix).push_back(row);
    }
}

pair<float, float> recFM(vector<vector<float> > matrix, vector<vector<float> > coefMatrix) {
    while (matrix[0].size() > 2) {
        matrix = normalizeWorkMat(matrix);
        matrix = sortMat(matrix);
        vector<vector<float> > newMatrix = combineRows(matrix);
        matrix = newMatrix;
    }
    matrix = normalizeWorkMat(matrix);
    return calcBounds(matrix);
}

pair<float, float> calcBounds(vector<vector<float> > matrix) {
    float minUpper = FLT_MAX;
    float maxLower = -FLT_MAX;

    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][0] > 0) {
            minUpper = min(minUpper, matrix[i][1]);
        } else if (matrix[i][0] < 0) {
            maxLower = max(maxLower, -matrix[i][1]);
        }
    }
    return make_pair(maxLower, minUpper);
}

vector<vector<float> > normalizeWorkMat(vector<vector<float> > workMat) {
    float constant;
    for (int i=0; i < workMat.size(); i++) {
        if (workMat[i][0] == 0) {
            continue;
        } else if (workMat[i][0] > 0) {
            constant = workMat[i][0];
        } else {
            constant = -workMat[i][0];
        }
        for (int j=0; j< workMat[i].size(); j++) {
            workMat[i][j] = workMat[i][j] / constant;
        }
    }
    return workMat;
}

vector<vector<float> > sortMat(vector<vector<float> > matrix) {
    int nextPos = 0;
    int nextEnd = matrix.size()-1; // last index

    for (int row = 0; row <= nextEnd; row++) { // should it be <=?
        while (matrix[nextPos][0] > 0) {
            nextPos++;
        }
        if (row < nextPos) {
            row = nextPos;
        }

        if (matrix[row][0] == 0) {
            matrix[row].swap(matrix[nextEnd]);
            nextEnd--;
        } else if (matrix[row][0] > 0) {
            matrix[row].swap(matrix[nextPos]);
            nextPos++;
        }
    }
    return matrix;
}

vector<vector<float> > combineRows(vector<vector<float> > matrix) {
    vector<vector<float> > newMatrix;

    int pos = findFirstPos(matrix);
    int neg = findFirstNeg(matrix);
    int end = matrix.size()-1;

    if (pos != -1 && neg != -1) {
        while (matrix[pos][0] > 0) {
            neg = findFirstNeg(matrix);
            while(matrix[neg][0] < 0) {
                vector<float> newRow;
                for (int i=1; i < matrix[pos].size(); i++) {
                    newRow.push_back(matrix[pos][i]+matrix[neg][i]);
                } 
                newMatrix.push_back(newRow);
                neg++;
            }
            pos++;
        }
    }
    while (matrix[end][0] == 0) {
        vector<float> newRow;
        copy(++matrix[end].begin(), matrix[end].end(), back_inserter(newRow));
        end--;
        newMatrix.push_back(newRow);
    }
    return newMatrix;
}



