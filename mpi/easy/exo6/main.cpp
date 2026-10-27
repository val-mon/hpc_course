#include <iostream>
#include "mpi.h"

using namespace std;
int main(int argc, char** argv){
    // init mpi
    MPI_Init(&argc, &argv);

    // get number of proc
    int nb_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    // get proc rank
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // array init
    int size = 1e6;
    int* local_vector = new int[size];
    for (int i = 0; i < size; i++){
        local_vector[i] = rand() % 1000;
    }

    // local vector sum
    int local_max = local_vector[0];
    for (int i = 1; i < size; i++){
        if (local_vector[i] > local_max){
            local_max = local_vector[i];
        }
    }
    
    // gather all maximums
    int* maximums = new int[nb_proc];
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Gather.html
    MPI_Gather(&local_max, 1, MPI_INT, maximums, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank==0){
        for (int i = 0; i < nb_proc; i++){
            cout << "Rank: " << i << ", maximum is: "<< maximums[i]<< "\n";
        }
    }

    // free resources
    delete[] local_vector;
    delete[] maximums;
    MPI_Finalize();
    return 0;
}
