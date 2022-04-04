#include "plant.h"
#include "functions.hpp"

int main()
{
    
    int N, k;
    vector<int> M;
    vector<double> a, b, g, TEP1, TEP2;
    
    getInitialData (N, k, M, a, b, g);
    
    Plant plant;
    plant_init(plant);
    int in_channel;
    
    vector<vector<double>>X(k,vector<double>(N)); // Объявление вектора на k строк по N элементов
    
    for (int i = 0; i < k; i++)     // Цикл, который идёт по строкам (каналам)
    {
        in_channel = M[i];
        for (int j = 0; j < N; j++) // Цикл, который идёт по элементам (номеру опроса)
        {
            X[i][j] = plant_measure(in_channel, plant); // Заполнение вектора
        }
    }
    
    calculateTEP1 (N, k, a, X, TEP1);
    calculateTEP2 (N, k, b, g, X, TEP2);
    
    viewingTable(N, k, M, X, TEP1, TEP2);
        
    return 0;
}
