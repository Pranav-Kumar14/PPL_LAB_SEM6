#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int power = 1;
    for (int i = 0; i < rank; i++) power *= 5;
    printf("Power of 5^%d : %d\n", rank, power);
    printf("Processor Rank %d: %s\n", rank, (rank % 2 == 0) ? "Hello!" : "World!");
    MPI_Finalize();
    return 0;
}
