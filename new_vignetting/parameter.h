class Parameter {
public:
    Parameter();

    Parameter(double value, double coefficient);

    double GetValue() const;

    double GetCoefficient() const;

    double GetLoss() const;

    void SetValue(double value);

    void SetCoefficient(double coefficient);

    void SetLoss(double loss);

    Parameter &operator = (const Parameter &other);

private:
    double value_;
    double coefficient_;
    double loss_;
};
