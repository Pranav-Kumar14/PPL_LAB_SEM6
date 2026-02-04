#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, M;
    float arr[100], local[50];
    float local_avg, avgs[10], total_avg = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter M: ");
        scanf("%d", &M);
        printf("Enter %d elements:\n", M * size);
        for (int i = 0; i < M * size; i++)
            scanf("%f", &arr[i]);
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, M, MPI_FLOAT, local, M, MPI_FLOAT, 0, MPI_COMM_WORLD);
    float sum = 0;
    for (int i = 0; i < M; i++)
        sum += local[i];
    local_avg = sum / M;
    MPI_Gather(&local_avg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i++)
            total_avg += avgs[i];
        total_avg /= size;
        printf("Total Average = %.2f\n", total_avg);
    }
    MPI_Finalize();
    return 0;
}
