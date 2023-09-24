#include "parameter.h"

Parameter::Parameter() : value_(1), coefficient_(0.001), loss_(0) {}

Parameter::Parameter(double value, double coefficient) : value_(value), coefficient_(coefficient), loss_(0) {}

double Parameter::GetValue() const {
    return this->value_;
}

double Parameter::GetCoefficient() const {
    return coefficient_;
}

double Parameter::GetLoss() const {
    return loss_;
}

void Parameter::SetValue(double value) {
    this->value_ = value;
}

void Parameter::SetCoefficient(double coefficient) {
    this->coefficient_ = coefficient;
}

void Parameter::SetLoss(double loss) {
    loss_ = loss;
}

//Перегружаем оператор присваивания
Parameter &Parameter::operator=(const Parameter &other) {
    this->value_ = other.value_;
    this->coefficient_ = other.coefficient_;
    return *this;
}


