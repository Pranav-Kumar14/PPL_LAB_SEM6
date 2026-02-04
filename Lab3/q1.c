#include<mpi.h>
#include<stdio.h>

int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int num, fact, sum = 0;
    int arr[10], facts[10];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter %d numbers:\n", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Scatter(arr, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fact = factorial(num);
    MPI_Gather(&fact, 1, MPI_INT, facts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i++)
            sum += facts[i];
        printf("Sum of factorials = %d\n", sum);
    }
    return 0;
}