#include <mpi.h>
#include <stdio.h>

int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank % 2 == 0)
        printf("Rank %d: Factorial = %d\n", rank, factorial(rank));
    else
        printf("Rank %d: Fibonacci = %d\n", rank, fibonacci(rank));
    MPI_Finalize();
    return 0;
}