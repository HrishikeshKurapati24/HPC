#include <vector>
#include <omp.h>
#include <math.h>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
# define p 4 // number of threads
void matrix_multiply(int n, ofstream &outfile){
    int sqrt_p = sqrt(p);

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

    #pragma omp parallel num_threads(p)
    {
        int thread_id = omp_get_thread_num();
        int row_block = thread_id / sqrt_p;
        int col_block = thread_id % sqrt_p;

        int row_start = (row_block * n) / sqrt_p;
        int row_end   = ((row_block + 1) * n) / sqrt_p;

        int col_start = (col_block * n) / sqrt_p;
        int col_end   = ((col_block + 1) * n) / sqrt_p;

        vector<int> local_y(n, 0);

        for(int i = row_start;i < row_end;i++){
            for(int j = col_start;j < col_end;j++){
                local_y[i] += matrix[i][j] * vec[j];
            }
        }

        #pragma omp critical
        {
            for(int i = row_start;i < row_end;i++){
                res[i] += local_y[i];
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    outfile<<n <<" "<<elapsed.count()<<endl;
}
int main() {
    vector<int> test_sizes = {10, 50, 100, 250, 500, 700, 900, 1000, 1500, 2000};

    ofstream outfile("2d_partitioning_results.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open results.txt for writing!" << std::endl;
        return 1;
    }

    for(int i = 0;i < test_sizes.size();i++){
        matrix_multiply(test_sizes[i], outfile);
    }
    
    return 0;
}