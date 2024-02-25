#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cfloat>

using namespace std;

void readInputs(int* width, int* height, vector<vector<float> >* initMatrix, vector<vector<float> >* coefMatrix);
bool solveFM(int width, int height, vector<vector<float> > initMatrix, vector<vector<float> > coefMatrix);
void divideRowByConstant(float** array, int rowNum, int width, float constant);
void swapRows(vector<vector<float> >* mat, int row1, int row2, int width);

int main() {

    int w;
    int h;
    vector<vector<float> > initMatrix;
    vector<vector<float> > coefMatrix;

    readInputs(&w, &h, &initMatrix, &coefMatrix);

    bool result;
    result = solveFM(w, h, initMatrix, coefMatrix);

    int pos = 0;
    int zero = h-1;
    int col = 0;

    /*
    while (pos < zero) {
        if (array[(pos+1)][col] > 0) {
            pos++;
        } else if (array[(zero-1)][col] == 0) {
            zero--;
        } else {
            int neg = pos + 1;
            while (array[neg][col] < 0) {
                neg++;
            }
        }
    }
    */
    /*
    Sort/swap rows (new matrix?)
        Pointer to lowest non-zero row
        Pointer to highest negative row
        Iterate to find next positive row
        Swap negative and positive, or abort

    Adjust row constants
        for each row:
            Divide by constant

    create new matrix by adding
    
    */

   /*
    iterate down
    if 0: swap to bottom
    if 1: swap to top
   */
    return 0;
}

void readInputs(int* width, int* height, vector<vector<float> >* initMatrix, vector<vector<float> >* coefMatrix) {
    cin >> *width;
    cin >> *height;
    for (int i=0; i<*height; i++) {
        vector<float> row;
        for (int j=0; j<*width; j++) {
            if (i==j) {
                row.push_back(1.0);
            } else {
                row.push_back(0.0);
            }
        }
        (*coefMatrix).push_back(row);
    }

    for (int j=0; j<*height; j++) {
        vector<float> row;
        for (int i=0; i<*width; i++) {
                float temp;
                cin >> temp;
                row.push_back(temp);
            }
        (*initMatrix).push_back(row);
    }
}

bool solveFM(int width, int height, vector<vector<float> > initMatrix, vector<vector<float> > coefMatrix) {

    vector<vector<float> > workMat = initMatrix;
    int pos = 0;
    int end = workMat.size();
    int newWidth = width;
    int newHeight = height;

    float constant;
    // normalize first matrix
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

    cout << "firstNormalization: " << endl;
    for (int i = 0; i < workMat.size(); i++) {
        for (int j = 0; j < workMat[i].size(); j++) {
            cout << " " << workMat[i][j];
        }
        cout << endl;
    }

    while (width > 2) {
        cout << "inside solveFM while loop" << endl;
        // order rows
        int pos = 0;
        int end = workMat.size();
        for (int i = 0; i < end; i++) {
            // cout << "inside for loop" << endl;
            if (workMat[i][0] > 0) {
                // cout << "pos row" << endl;
                workMat[i].swap(workMat[pos]); // swapRows(&workMat, pos, i, width);
                pos++;
            } else if (workMat[i][0] == 0) {
                // cout << "zerorow" << endl;
                end--;
                workMat[i].swap(workMat[end]); // swapRows(&workMat, i, end, width);
                i--;
            }
        }
        cout << "sorted:" << endl;
        for (int i = 0; i < workMat.size(); i++) {
            for (int j = 0; j < workMat[i].size(); j++) {
                cout << " " << workMat[i][j];
            }
            cout << endl;
        }
        
        cout << "doing  new mat calc" << endl;
        newWidth = width - 1;
        vector<vector<float> > newMat;
        if (pos == 0 || end - pos <= 0) {
            newHeight = height;
            cout << "first cond" << endl;
            for (int i=0; i < newHeight; i++) {
                if (workMat[i][0] != 0) {
                    continue;
                } else {
                    cout << "i= " << i << endl;
                    vector<float> temp (newWidth);
                    newMat.push_back(temp);
                    auto start = workMat[i].begin();
                    ++start;
                    cout << "just preseg" << endl;
                    copy(start, workMat[i].end(), newMat[newMat.size()-1].begin());
                }
            }
        } else {
            cout << "else cond:" << endl;
            cout << "width = " << width << endl;
            newHeight = (pos) * (end - pos) + (workMat.size() - end);
            int posIt = 0;
            int negIt = pos;
            vector<float> row;

            cout << "preLoop: " << "postIt = " << posIt << " negIt = " << negIt << endl;
            
            while (posIt < pos) {
                while (negIt < end) {
                    vector<float> row;
                    for (int i = 1; i < width; i++) {
                        cout << "postIt = " << posIt << " negIt = " << negIt << " i= " << i << endl;
                        row.push_back(workMat[posIt][i] + workMat[negIt][i]);
                    }
                    newMat.push_back(row);
                    negIt++;
                }
                negIt = pos;
                posIt++;
            }
            cout << endl;
            int endIt = end + 1;
            while (endIt < workMat.size()) {
                vector<float> temp (newWidth);
                newMat.push_back(temp);
                auto start = workMat[endIt].begin();
                ++start;
                copy(start, workMat[endIt].end(), newMat[newMat.size()-1].begin());
                endIt++;
            }
            
        }

        workMat = newMat;
        width = newWidth;
        height = newHeight;

        // normalize matrix
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
        
        for (int i = 0; i < workMat.size(); i++) {
            for (int j = 0; j < workMat[i].size(); j++) {
                cout << " " << workMat[i][j];
            }
            cout << endl;
        }

    }

    float minUpper = FLT_MAX;
    float maxLower = -FLT_MAX;

    for (int i = 0; i < workMat.size(); i++) {
        if (workMat[i][0] > 0) {
            if (workMat[i][1] < minUpper) {
                minUpper = workMat[i][1];
            }
        } else if (workMat[i][0] < 0) {
            if (workMat[i][1] > maxLower) {
                maxLower = workMat[i][1];
            }
        }
    }
    if (maxLower <= minUpper) {
        cout << "lower <= upper" << endl;
        cout << maxLower << " " << minUpper << endl;
        return true;
    } else {
        cout << "lower > upper" << endl;
        cout << maxLower << " " << minUpper << endl;
        return false;
    }
}

/*
vector<vector<float>> orderFM(vector<vector<float>> workMat) {
    
}
*/

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