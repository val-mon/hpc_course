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

    // print hello
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Recv.html
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Send.html
    if(rank == 0){
        cout << "Number of processors: " << nb_proc << endl;
        cout << rank << ": hello" << endl;
        if (nb_proc > 1){
            int sig = 1;
            MPI_Send(&sig, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }
    } else {
        int signal;
        MPI_Recv(&signal, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << rank << ": hello" << endl;
        
        if (rank < nb_proc - 1){
            int sig = 1;
            MPI_Send(&sig, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
    }

    // free resources
    MPI_Finalize();

    return 0;
}
