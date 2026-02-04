#include <mpi.h>
#include <stdio.h>

int reverse(int n) {
    int r = 0;
    while (n > 0) {
        r = r * 10 + (n % 10);
        n /= 10;
    }
    return r;
}

int main(int argc, char *argv[]) {
    int rank;
    int arr[8] = {18, 523, 301, 1234, 2, 14, 108, 1928};
    int num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Scatter(arr, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    num = reverse(num);
    MPI_Gather(&num, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Reversed array:\n");
        for (int i = 0; i < 8; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}