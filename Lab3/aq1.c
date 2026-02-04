#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size, M;
    int arr[100], local[100], result[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter M: ");
        scanf("%d", &M);
        printf("Enter %d elements:\n", size * M);
        for (int i = 0; i < size * M; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, M, MPI_INT, local, M, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < M; i++)
        local[i] = pow(local[i], rank + 2);
    MPI_Gather(local, M, MPI_INT, result, M, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Result array:\n");
        for (int i = 0; i < size * M; i++)
            printf("%d ", result[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
