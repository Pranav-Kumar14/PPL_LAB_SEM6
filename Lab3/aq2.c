#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    int arr[100], local[20], result[100];
    int even = 0, odd = 0, total_even = 0, total_odd = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter N: ");
        fflush(stdout);
        scanf("%d", &N);
        printf("Enter %d elements:\n", N);
        fflush(stdout);
        for (int i = 0; i < N; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, N / size, MPI_INT, local, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < N / size; i++) {
        if (local[i] % 2 == 0) {
            local[i] = 1;
            even++;
        } else {
            local[i] = 0;
            odd++;
        }
    }
    MPI_Gather(local, N / size, MPI_INT, result, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&even, &total_even, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&odd, &total_odd, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Resultant array:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", result[i]);
        printf("\nEven = %d\nOdd = %d\n", total_even, total_odd);
    }
    MPI_Finalize();
    return 0;
}
