#include <iostream>
#include <fstream>
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

    // get line
    string line;
    int size;
    if (rank == 0) {
        ifstream file("data.txt");

        if (!file.is_open()) {
            cerr << "Error during file opening\n";

            // https://www.mpich.org/static/docs/v3.2/www3/MPI_Abort.html
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        getline(file, line);
        size = line.size();
        file.close();
    }

    // send size to all proc
    // https://www.mpich.org/static/docs/v3.2/www3/MPI_Bcast.html
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        // allocate the necessary space for the string because only rank0 know line
        line.resize(size);
    }

    // send line to all rank
    MPI_Bcast(&line[0], size, MPI_CHAR, 0, MPI_COMM_WORLD);
    cout << "Processus " << rank << " a reçu : " << line << endl;

    // free resources
    MPI_Finalize();
    return 0;
}
