#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void getInitialData(int& N, int& k, vector<int>& M, vector<double>& a, vector<double>& b, vector<double>& g);
void calculateTEP1 (int N, int k, vector<double> a, vector<vector<double>> X, vector<double>& TEP1);
void calculateTEP2 (int N, int k, vector<double> b, vector<double> g, vector<vector<double>> X, vector<double>& TEP2);
void viewingTable (int N, int k, vector<int> M, vector<vector<double>> X, vector<double> TEP1, vector<double> TEP2);

#endif /* functions_hpp */
