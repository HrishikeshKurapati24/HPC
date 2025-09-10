#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

void matrix_multiply(int n, ofstream &outfile){
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<int> vec(n, 0);
    vector<int> res(n, 0);

    srand(time(NULL));

    for(int i = 0;i < n;i++){
        for (int j = 0;j < n;j++){
            matrix[i][j] = rand() % 100 + 1;
        }
    }

    for(int j = 0;j < n;j++){
        vec[j] = rand() % 100 + 1;
    }

    auto startTime = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int rows_per_thread = n / num_threads;
        int start = thread_id * rows_per_thread;
        int end = (thread_id == num_threads - 1) ? n : start + rows_per_thread;

        for(int i = start;i < end;i++){
            int sum = 0;
            for(int j = 0;j < n;j++){
                sum += matrix[i][j] * vec[j];
            }

            res[i] = sum;
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    outfile<<n <<" "<<elapsed.count()<<endl;
}

int main() {
    vector<int> test_sizes = {10, 50, 100, 250, 500, 700, 900, 1000, 1500, 2000};

    ofstream outfile("1d_partitioning_results.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open results.txt for writing!" << std::endl;
        return 1;
    }

    for(int i = 0;i < test_sizes.size();i++){
        matrix_multiply(test_sizes[i], outfile);
    }
    
    return 0;
}