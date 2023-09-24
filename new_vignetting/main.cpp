#include "function.h"

using namespace std;

void FillData(vector<vector<double>> &realData, int height, int width);

void PrintData(vector<vector<double>> &realData, int height, int width);

//Считываем реальные данные для образца -> создаем объект function -> используем градиентный спуск для function
int main() {
    int height, width;
    cin >> height >> width;
    vector<vector<double>> realData(height, vector<double>(width));
    FillData(realData, height, width);
    double coef = 0.001;
    Function function(Parameter(-1, coef), Parameter(-1, coef),
                      Parameter(-1, coef), Parameter(1, coef),
                      Parameter(1, coef), Parameter(0, coef), height, width);

    function.GradientDescent(realData);
    PrintData(realData, height, width);
    function.PrintPrediction();
    function.PrintParameters();
    return 0;
}

//Запонлняем массив верными данными
void FillData(vector<vector<double>> &realData, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cin >> realData[i][j];
        }
    }
    std::cout << "\n";
}

//Выводим значения массива
void PrintData(vector<vector<double>> &realData, int height, int width) {
    cout << "Real data:\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << realData[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}