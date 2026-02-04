#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n = 1000000;
    double h, sum = 0, x, pi;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    h = 1.0 / n;
    for (int i = rank; i < n; i += size) {
        x = h * (i + 0.5);
        sum += 4.0 / (1.0 + x * x);
    }
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("PI = %f\n", pi * h);
    MPI_Finalize();
    return 0;
}
