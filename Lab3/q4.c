#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, chunk;
    char s1[100], s2[100];
    char l1[20], l2[20], lres[40];
    char result[200];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        scanf("%s %s", s1, s2);
        chunk = strlen(s1) / size;
    }
    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(s1, chunk, MPI_CHAR, l1, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, chunk, MPI_CHAR, l2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    int k = 0;
    for (int i = 0; i < chunk; i++) {
        lres[k++] = l1[i];
        lres[k++] = l2[i];
    }
    MPI_Gather(lres, 2*chunk, MPI_CHAR, result, 2*chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Resultant string: %s\n", result);
    MPI_Finalize();
    return 0;
}
