#include <iostream>
#include <vector>
#include <math.h>
#include "plant.h"
#include <iomanip>
using namespace std;

void getDatas (int& N, int& b, int& M, double& gmin, double& gmax, double& step);
void calculateTEP2_for1channel (int N, int b, double g, vector<double> X, double& TEP2);

int main() {
    
    int N, M, b;
    double gmin, gmax, step, TEP2;
    vector<double> result, g;
    
    Plant plant;
    plant_init(plant);
    int in_channel;
    
    getDatas (N, b, M, gmin, gmax, step);
    
    vector<double>X (N);
    
    in_channel = M;
    for (int i = 0; i < N; i++)
    {
        X[i] = plant_measure(in_channel, plant);
    }

    int steps = fabs( (gmax - gmin)/step );
    g.resize(steps);
    result.resize(steps);
    g[0]=gmin;
    for (int i = 0; i < steps; i++)
    {
        calculateTEP2_for1channel (N, b, g[i], X, TEP2);
        result[i] = TEP2;
        g[i+1] = g[i] + step;
    }
    
    cout << "N" << "\t" << "g" << "\t" << "TEP2" << "\n";
    for (int i = 0; i < steps; i++)
    {
        cout << i + 1;
        cout << "\t";
        cout.unsetf(ios_base::fixed);
        cout << setprecision(8);
        cout << g[i];
        cout << "\t";
        cout << fixed << setprecision(1);
        cout << result[i];
        cout << "\n";
    }

    double min = result[0];
    int j, jmin = 0;
    for (j = 0 ; j < steps; j++) {
        if (result[j] < min) {
            min = result[j];
            jmin = j;
        }
    }
    cout << "\n" << "Минимальный TEP2 \'" << min << "\'\nНа " << jmin + 1 << " шаге, при g \'" << g[jmin] << "\'\n" << "На " << M << " канале опроса, опрашивая " << N << " раз\n\n";
    return 0;
}
void
getDatas (int& N, int& b, int& M, double& gmin, double& gmax, double& step) {
    
    setlocale(LC_ALL, "ru");
    bool correctInput = false;
    size_t counter = 0;
    
    while(!correctInput && counter < 15) {
        cerr << "Введите число опросов по каналу: ";
        cin >> N;
        if (N < 0)
        {
            cerr << "Число опросов не может быть отрицательным\n";
            counter++;
        }
        else
        {
            correctInput = true;
        }
    }
    
    correctInput = false;
    counter = 0;
    while (!correctInput && counter < 15) {
        cerr << "Введите номер канала опроса: ";
        cin >> M;
        if (M < 0 || M > 99)
        {
            cerr << "Введено число вне диапозона от 1 до 99\n";
            counter++;
        }
        else
        {
            correctInput = true;
        }
    }
    cerr << "Примем множитель \'b\' за \'1\'\n";
    b = 1;
    cerr << "Введите минимальное значение \'g\': ";
    cin >> gmin;
    cerr << "Введите максимальное значение \'g\': ";
    cin >> gmax;
    
    correctInput = false;
    counter = 0;
    while(!correctInput && counter < 100) {
        cerr << "Введите шаг по \'g\': ";
        cin >> step;
        if (step < 0)
        {
            cerr << "Введено не положительное число\n";
            counter++;
        }
        else if (step > (gmax - gmin) ) {
            cerr << "Длина шага превышает диапозон по \'g\'\n";
            counter++;
        }
        else
        {
            correctInput = true;
        }
    }
    cerr << "\n";
}
void
calculateTEP2_for1channel (int N, int b, double g, vector<double> X, double& TEP2)
{
    double sumXg = 0;
    for (size_t i = 0; i < N; i++)
    {
        sumXg += pow( X[i] - g ,2);
    }
    TEP2 = b * sumXg / N;
}
