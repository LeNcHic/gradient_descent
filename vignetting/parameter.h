class Parameter {
public:
    Parameter();
    Parameter(double value, double coefficient);
    double GetValue() const;
    double GetCoefficient() const;
    void SetValue(double value);
    void SetCoefficient(double coefficient);

private:
    double value_;
    double coefficient_;
};
