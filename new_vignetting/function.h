#include <vector>
#include <iostream>
#include <iomanip>
#include "parameter.h"

class Function {
public:
    Function();
    Function(Parameter A, Parameter B, Parameter C, Parameter D, Parameter E, Parameter F, int height, int width);

    int GetHeight() const;
    int GetWidth() const;
    void SetWidth(int width);
    void SetHeight(int height);
    void PrintPrediction() const;
    double GetFunctionRes(double x, double y) const;
    double GetDerivative(double realValue, double predictValue,  double x, double y);
    double UpdateParameters(std::vector<std::vector<double>> &realData);
    void GradientDescent(std::vector<std::vector<double>> &realData);
    void PrintParameters() const;


private:
    Parameter A_;
    Parameter B_;
    Parameter C_;
    Parameter D_;
    Parameter E_;
    Parameter F_;
    int height_;
    int width_;
};

