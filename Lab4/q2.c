#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, key, local_count = 0, total;
    int mat[3][3], row[3];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                scanf("%d", &mat[i][j]);
        scanf("%d", &key);
    }
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(mat, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 3; i++)
        if (row[i] == key) local_count++;
    MPI_Reduce(&local_count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Occurrences = %d\n", total);
    MPI_Finalize();
    return 0;
}
