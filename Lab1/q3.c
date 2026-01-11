#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char hello[] = "HELLO";
    if (rank < 5) {
        hello[rank] += ('a' - 'A');
        printf("Rank %d toggling %d character: %s\n", rank, rank, hello);
    }
    MPI_Finalize();
    return 0;
}
