#include <iostream>
#include <vector>
#include <iomanip>
#include "parameter.h"
using namespace std;

void FillData(vector<vector<double>> &realData, int height, int width);
void PrintData(vector<vector<double>> &realData, int height, int width);
void PrintPrediction(double A, double B, double C, double D, double E, double F, int height, int width);
double GetFunctionRes(double A, double B, double C, double D, double E, double F, int index_i, int index_j, int height, int width);
double GetDerivative(double realValue, double functionRes, double x, double y);
bool UpdateParameters(Parameter &parameterA, Parameter &parameterB, Parameter &parameterC, Parameter &parameterD,
                      Parameter &parameterE, Parameter &parameterF, vector<vector<double>> &realData, int height, int width);

int main() {
    int width, height;
    cin >> height >> width;
    vector<vector<double>> realData(height, vector<double>(width));
    FillData(realData, height, width);
    Parameter parameterA;
    Parameter parameterB;
    Parameter parameterC;
    Parameter parameterD;
    Parameter parameterE;
    Parameter parameterF(0, 0.01);
    //PrintPrediction(parameterA.GetValue(), parameterB.GetValue(), parameterC.GetValue(), parameterD.GetValue(), parameterE.GetValue(), parameterF.GetValue(), height, width);
    for (int i = 0; i < 100000; ++i) {
        PrintPrediction(parameterA.GetValue(), parameterB.GetValue(), parameterC.GetValue(), parameterD.GetValue(), parameterE.GetValue(), parameterF.GetValue(), height, width);
        cout << "\n";
        if (UpdateParameters(parameterA, parameterB, parameterC, parameterD, parameterE, parameterF, realData, height, width)) {
            cout << i << "\n";
            break;
        };
    }
    PrintData(realData, height, width);
    PrintPrediction(parameterA.GetValue(), parameterB.GetValue(), parameterC.GetValue(), parameterD.GetValue(), parameterE.GetValue(), parameterF.GetValue(), height, width);
    cout << fixed << setprecision(5) << parameterA.GetValue() << " " << parameterB.GetValue() << " " << parameterC.GetValue() << " " << parameterD.GetValue() << " " << parameterE.GetValue() << " " << parameterF.GetValue();
    return 0;
}

void FillData(vector<vector<double>> &realData, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cin >> realData[i][j];
        }
    }
}

void PrintData(vector<vector<double>> &realData, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << realData[i][j] << " ";
        }
        cout << "\n";
    }
}

double GetFunctionRes(double A, double B, double C, double D, double E, double F, int index_i, int index_j, int height, int width) {
    double x, y;
    x = double(index_i) / height;
    y = double(index_j) / width;
    return A * x * x + B * y * y + C * x * y + D * x + E * y + F;
}

void PrintPrediction(double A, double B, double C, double D, double E, double F, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << setprecision(4) << abs(GetFunctionRes(A, B, C, D, E, F, i, j, height, width)) << " ";
        }
        cout << "\n";
    }
}

double GetDerivative(double realValue, double functionRes, double x, double y) {
    return 2 * (functionRes - realValue) * x * y;
}

bool UpdateParameters(Parameter &parameterA, Parameter &parameterB, Parameter &parameterC, Parameter &parameterD,
                      Parameter &parameterE, Parameter &parameterF, vector<vector<double>> &realData, int height, int width) {
    double lossA = 0, lossB= 0, lossC = 0, lossD = 0, lossE = 0, lossF = 0;
    double functionRes;
    double A = parameterA.GetValue();
    double B = parameterB.GetValue();
    double C = parameterC.GetValue();
    double D = parameterD.GetValue();
    double E = parameterE.GetValue();
    double F = parameterF.GetValue();
    double difference = 0;
    bool flag = false;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            functionRes = GetFunctionRes(A, B, C, D, E, F, i, j, height, width);
            lossA += GetDerivative(realData[i][j], functionRes, double(i) / height,double(i) / height);
            lossB += GetDerivative(realData[i][j], functionRes, double(j) / width, double(j) / width);
            lossC += GetDerivative(realData[i][j], functionRes, double(i) / height, double(j) / width);
            lossD += GetDerivative(realData[i][j], functionRes, double(i) / height, 1);
            lossE += GetDerivative(realData[i][j], functionRes, 1, double(j) / width);
            lossF += GetDerivative(realData[i][j], functionRes, 1, 1);
            difference += abs(functionRes - realData[i][j]);
        }
    }
    parameterA.SetValue(A - parameterA.GetCoefficient() * lossA / (height * width));
    parameterB.SetValue(B - parameterB.GetCoefficient() * lossB / (height * width));
    parameterC.SetValue(C - parameterC.GetCoefficient() * lossC / (height * width));
    parameterD.SetValue(D - parameterD.GetCoefficient() * lossD / (height * width));
    parameterE.SetValue(E - parameterE.GetCoefficient() * lossE / (height * width));
    parameterF.SetValue(F - parameterF.GetCoefficient() * lossF / (height * width));
    if (difference < 0.01 * height * width) {
        flag = true;
    }
    return flag;
}


//10 10
//0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1
//0.1 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.1
//0.1 0.2 0.2 0.3 0.3 0.3 0.3 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.4 0.4 0.4 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.7 0.9 0.7 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.7 0.9 0.7 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.4 0.4 0.4 0.2 0.2 0.1
//0.1 0.2 0.2 0.3 0.3 0.3 0.3 0.2 0.2 0.1
//0.1 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.1
//0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1



//4 4
//0.1 0.1 0.1 0.1
//0.1 0.2 0.2 0.1
//0.1 0.9 0.9 0.1
//0.1 0.1 0.1 0.1

//6 6
//0.1 0.1 0.1 0.1 0.1 0.1
//0.1 0.2 0.2 0.2 0.2 0.1
//0.1 0.2 0.3 0.3 0.3 0.1
//0.1 0.2 0.3 0.4 0.3 0.1
//0.1 0.2 0.2 0.2 0.2 0.1
//0.1 0.1 0.1 0.1 0.1 0.1

//10 10
//0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1
//0.1 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.1
//0.1 0.2 0.2 0.3 0.3 0.3 0.3 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.4 0.4 0.4 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.5 0.5 0.5 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.5 0.5 0.5 0.2 0.2 0.1
//0.1 0.2 0.2 0.4 0.4 0.4 0.4 0.2 0.2 0.1
//0.1 0.2 0.2 0.3 0.3 0.3 0.3 0.2 0.2 0.1
//0.1 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.1
//0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1

//15 4
//0.1 0.1 0.1 0.1
//0.1 0.2 0.2 0.1
//0.1 0.3 0.3 0.1
//0.1 0.4 0.3 0.1
//0.1 0.5 0.5 0.1
//0.1 0.6 0.6 0.1
//0.1 0.7 0.7 0.1
//0.1 0.8 0.8 0.1
//0.1 0.7 0.7 0.1
//0.1 0.6 0.6 0.1
//0.1 0.5 0.5 0.1
//0.1 0.4 0.4 0.1
//0.1 0.3 0.3 0.1
//0.1 0.2 0.2 0.1
//0.1 0.1 0.1 0.1