#include "parameter.h"

Parameter::Parameter(): value_(1), coefficient_(0.01) {}

Parameter::Parameter(double value, double coefficient): value_(value), coefficient_(coefficient) {}

void Parameter::SetValue(double value) {
    this->value_ = value;
}

double Parameter::GetValue() const {
    return this->value_;
}

double Parameter::GetCoefficient() const {
    return coefficient_;
}

void Parameter::SetCoefficient(double coefficient) {
    this->coefficient_ = coefficient;
}
