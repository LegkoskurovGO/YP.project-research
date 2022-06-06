#include "functions.hpp"

void
getInitialData(int& N, int& k, vector<int>& M, vector<double>& a, vector<double>& b, vector<double>& g)
{
    
    setlocale(LC_ALL, "ru");
    bool correctInput;
    size_t counter;
    
    correctInput = false;
    counter = 0;
    while(!correctInput && counter < 100) {
        
        cerr << "Введите число опросов по каждому каналу: ";
        cin >> N;
        
        if(N > 0) {
            correctInput = true;
        } else {
            std::cerr << "Число опросов не может быть отрицательным\n";
            counter++;
        }
    }
    
    correctInput = false;
    counter = 0;
    while(!correctInput && counter < 100) {
        
        cerr << "Введите число каналов опроса: ";
        cin >> k;
        if(1 <= k && k <= 6) {
            correctInput = true;
        } else {
            cerr << "Каналы опроса '1 - 6', введите данные заново\n";
            counter++;
        }
    }
    M.resize(k);
    a.resize(k);
    b.resize(k);
    g.resize(k);
    
    correctInput = false;
    counter = 0;
    while(!correctInput && counter < 100) {
        
        cerr << "Введите номера каналов опроса через пробел: ";
        size_t i;
        for (i = 0; i < k; i++) {
            cin >> M[i];
        }
        i = 0;
        while (!correctInput && i < k) {
            if (M[i] < 1 || M[i] > 6) {
                cerr << "Каналы опроса \'1 - 6\', введите данные заново\n";
                counter++;
                i = k;
            }
            i++;
        }
        if (i == k) {
            correctInput = true;
        }
    }
   
    for (size_t i = 0; i < k; i++) {
            cerr << "Введите константы для " << M[i] << " канала: \n";
            cerr << "\ta" << M[i] << ": ";
            cin >> a[i];
            cerr << "\tb" << M[i] << ": ";
            cin >> b[i];
            cerr << "\tg" << M[i] << ": ";
            cin >> g[i];
    }
    cerr << "\n\n";
}
void
calculateTEP1 (int N, int k, vector<double> a, vector<vector<double>> X, vector<double>& TEP1)
{
    TEP1.resize(k);
    for (size_t i = 0; i < k; i++)
    {
        double sumX = 0;
        for (size_t j = 0; j < N; j++)
        {
            sumX += X[i][j];
        }
        TEP1[i] = a[i] * sumX / N;
    }
}
void
calculateTEP2 (int N, int k, vector<double> b, vector<double> g, vector<vector<double>> X, vector<double>& TEP2)
{
    TEP2.resize(k);
    for (size_t i = 0; i < k; i++)
    {
        double sumXg = 0;
        for (size_t j = 0; j < N; j++)
        {
            sumXg += pow( X[i][j] - g[i] ,2);
        }
        TEP2[i] = b[i] * sumXg / N;
    }
}
void
viewingTable (int N, int k, vector<int> M, vector<vector<double>> X, vector<double> TEP1, vector<double> TEP2)
{
    cout << "N" << "\t";
    for (size_t i = 0; i < k; i++)
    {
        cout << "X" << M[i] << "\t\t";
    }
    cout << "\n";
    
    for (size_t j = 0; j < N; j++)
    {
        cout << j + 1 << "\t";
        for (size_t i = 0; i < k; i++)
        {
            cout << X[i][j];
            if (M[i] == 1 && X[i][j] < 1) {
                cout << "   \t";
            } else {
                cout << "\t\t";
            }
        }
        cout << "\n";
    }
    
    for (size_t i = 0; i < k; i++)
    {
        cout << "----------------";
    }
    cout << "\n";
    
    cout << "M" << "\t";
    for (size_t j = 0; j < k; j++)
    {
        cout << M[j] << "\t\t";
    }
    cout << "\n";

    cout << "ТЭП1" << "\t";
    for (size_t j = 0; j < k; j++) {
        cout << TEP1[j] << "       \t";
    }
    cout << "\n";
    cout << "ТЭП2" << "\t";
    for (size_t j = 0; j < k; j++) {
        cout << TEP2[j] << "       \t";
    }
    cout << "\n\n";
}
