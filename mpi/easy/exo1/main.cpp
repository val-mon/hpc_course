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

    if(rank == 0){
        cout << "Number of processors: " << nb_proc << endl;
    }

    // print hello for every proc
    cout << rank << ": hello" << endl;

    // finalise mpi
    MPI_Finalize();

    return 0;
}
