#include <vector>
#include <math.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

void matrix_multiply(int n, ofstream &outfile){
    vector<vector<int> > matrix(n, vector<int>(n,0));
    vector<int> vec(n, 0);
    vector<int> res(n,0);

    srand(time(NULL));

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            matrix[i][j] = rand() % 100 + 1;
        }
    }

    for(int j = 0;j < n;j++){
        vec[j] = rand() % 100 + 1;
    }

    auto startTime = chrono::high_resolution_clock::now();

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            res[i]+= matrix[i][j] * vec[j];
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    outfile<<n <<" "<<elapsed.count()<<endl;
}

int main(){
    vector<int> test_sizes = {10, 50, 100, 250, 500, 700, 900, 1000, 1500, 2000};
    
    ofstream outfile("sequential_results.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open results.txt for writing!" << std::endl;
        return 1;
    }

    for(int i = 0;i < test_sizes.size();i++){
        matrix_multiply(test_sizes[i], outfile);
    }

    return 0;
}