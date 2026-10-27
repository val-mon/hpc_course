#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char** argv){
    // init mpi
    MPI_Init(&argc, &argv);

    // get number of processors
    int nb_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    // get processor rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // array init
    int chunk_size = 1e7;
    int size = nb_proc*chunk_size;
    int* local_vector = new int[chunk_size];
    int* global_vector = nullptr;

    // array scatter
    if (rank==0){
        global_vector = new int[size];
        long long sum = 0;
        for (int i = 0; i < size; i++){
            int n = rand() % 100;
            global_vector[i] = n;
            sum += n;
        }
        cout << sum << endl;
    }
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Scatter.html
    MPI_Scatter(global_vector, chunk_size, MPI_INT, local_vector, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // local sum
    long long local_sum = 0;
    for (int i = 0; i < chunk_size; i++){
        local_sum += local_vector[i];
    }

    // global sum
    long long global_sum;
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Reduce.html
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // print results
    if (rank==0){
        cout << global_sum << endl;
    }

    // free resources
    delete[] local_vector;
    if (rank == 0) {
        delete[] global_vector;
    }
    MPI_Finalize();
    return 0;
}
