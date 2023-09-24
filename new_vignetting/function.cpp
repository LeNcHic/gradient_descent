#include "function.h"


Function::Function(): A_(), B_(), C_(), D_(), E_(), F_(), height_(0), width_(0) {}

Function::Function(Parameter A, Parameter B, Parameter C, Parameter D, Parameter E, Parameter F, int height, int width) {
    A_ = A;
    B_ = B;
    C_ = C;
    D_ = D;
    F_ = F;
    width_ = width;
    height_ = height;
}

int Function::GetHeight() const {
    return height_;
}

int Function::GetWidth() const {
    return width_;
}

void Function::SetWidth(int width) {
    width_ = width;
}

void Function::SetHeight(int height) {
    height_ = height;
}

//Вывод таблицы, составленной из значений функции
void Function::PrintPrediction() const {
    std::cout << "Predicted data:\n";
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            std::cout << std::fixed << std::setprecision(4) << GetFunctionRes(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//Возвращаем значение функции в точке (x, y)
double Function::GetFunctionRes(double x, double y) const {
    x /=  height_;
    y /= width_;
    return A_.GetValue() * x * x + B_.GetValue() * y * y + C_.GetValue() * x * y + D_.GetValue() * x + E_.GetValue() * y + F_.GetValue();
}

//Общий вид производной функции Loss = (realData[x * height][y * width] - Ax^2 - By^2 - Cxy - Dx - Ey - F)^2
double Function::GetDerivative(double realValue, double predictValue,  double x, double y) {
    return 2 * (predictValue - realValue) * x * y;
}

//Покомпонентно обновляем каждый коэффициент функции, изпользуя формулу градиентного спуска
double Function::UpdateParameters(std::vector<std::vector<double>> &realData) {
    double predictValue, realValue;
    double difference = 0;
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            predictValue = GetFunctionRes(i, j);
            realValue = realData[i][j];
            A_.SetLoss(A_.GetLoss() + GetDerivative(realValue, predictValue, double(i) / height_, double(i) / height_));
            B_.SetLoss(B_.GetLoss() + GetDerivative(realValue, predictValue, double(j) / width_, double(j) / width_));
            C_.SetLoss(C_.GetLoss() + GetDerivative(realValue, predictValue, double(i) / height_, double(j) / width_));
            D_.SetLoss(D_.GetLoss() + GetDerivative(realValue, predictValue, double(i) / height_, 1));
            E_.SetLoss(E_.GetLoss() + GetDerivative(realValue, predictValue, 1, double(j) / width_));
            F_.SetLoss(F_.GetLoss() + GetDerivative(realValue, predictValue, 1, 1));
            difference += abs(realValue - predictValue);
        }
    }

    int size = height_ * width_;
    A_.SetValue(A_.GetValue() - A_.GetCoefficient() * A_.GetLoss() / size);
    B_.SetValue(B_.GetValue() - B_.GetCoefficient() * B_.GetLoss() / size);
    C_.SetValue(C_.GetValue() - C_.GetCoefficient() * C_.GetLoss()/ size);
    D_.SetValue(D_.GetValue() - D_.GetCoefficient() * D_.GetLoss() / size);
    E_.SetValue(E_.GetValue() - E_.GetCoefficient() * E_.GetLoss() / size);
    F_.SetValue(F_.GetValue() - F_.GetCoefficient() * F_.GetLoss() / size);
    return difference;
}

//Обновление коэффициентов функции 10^7 раз или пока разница между реальными и полученными значениями больше некоторого числа
void Function::GradientDescent(std::vector<std::vector<double>> &realData) {
    double difference = 100;
    int count = 0;
    while ((difference > 0.06) and (count < 10000000)) {
        difference = UpdateParameters(realData) / (height_ * width_);
        count++;
    }
    std::cout << count << " " << difference << "\n";
}

//Вывод коэффициентов функции с точностью в 5 знаков после запятой
void Function::PrintParameters() const {
    std::cout << std::fixed << std::setprecision(5)
    << "Parameters:"
    << "\nA: " << A_.GetValue()
    << "\nB: " << B_.GetValue()
    << "\nC: " << C_.GetValue()
    << "\nD: " << D_.GetValue()
    << "\nE: " << E_.GetValue()
    << "\nF: " << F_.GetValue()
    << "\n";
}
