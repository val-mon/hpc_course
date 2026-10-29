#include <iostream>
#include <chrono>
// #include <vector>
// #include <cassert>
// #include <cmath>
#include "mpi.h"

using namespace std;
using namespace chrono;

int* generate_vector(int size){
    int* data = new int[size]{0};
    for (int i = 0; i < size; i++){
        int rdm = rand() % 10;
        int sign = ((rand() % 10) > 5) ? -1 : 1;
        data[i] = rdm * sign;
    }
    return data;
}

int main(int argc, char** argv){
    // check arguments
    if (argc != 2){
        cerr << "Error: incorrect argements" << endl;
        cerr << "\tUsage: mpirun -np 4 ./run {vector size} " << endl;
        exit(1);
    }

    // init mpi
    MPI_Init(&argc, &argv);

    // get number of proc
    int nb_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    // get proc rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // vector scatter
    int vector_size = stoi(argv[1]);
    int chunk_size = vector_size/nb_proc;
    int* local_v1 = new int[chunk_size];
    int* local_v2 = new int[chunk_size];
    int* v1 = nullptr;
    int* v2 = nullptr;

    if(rank == 0){
        v1 = generate_vector(vector_size);
        v2 = generate_vector(vector_size);

        long long tot = 0;

        auto ref_start = high_resolution_clock::now();
        for (int i = 0; i < vector_size; i++){
            tot += v1[i]*v2[i];
        }
        auto ref_end = high_resolution_clock::now();

        double ref_time = duration_cast<milliseconds>(ref_end-ref_start).count();
        cout << "sum1: " << tot << endl;
        cout << "\t time = " << ref_time << "ms" << endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    auto ref_start = high_resolution_clock::now();

    MPI_Scatter(v1, chunk_size, MPI_INT, local_v1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(v2, chunk_size, MPI_INT, local_v2, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // product
    long long local_product = 0;
    long long global_sum;

    for (int i = 0; i < chunk_size; i++){
        local_product += local_v1[i]*local_v2[i];
    }
    MPI_Reduce(&local_product, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    auto ref_end = high_resolution_clock::now();
    double ref_time = duration_cast<milliseconds>(ref_end-ref_start).count();

    // print results
    if (rank==0){
        cout << "sum2: " << global_sum << endl;
        cout << "\t time = " << ref_time << "ms" << endl;
    }

    // free resources
    delete[] local_v1;
    delete[] local_v2;
    if (rank == 0) {
        delete[] v1;
        delete[] v2;
    }
    MPI_Finalize();
    return 0;
}
