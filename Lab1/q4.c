#include <mpi.h>
#include <stdio.h>

int fib(int n) {
    if (n <= 2) return 1;
    int a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int fact(int n) {
    int f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%s of rank %d : %d\n", rank % 2 ? "Fibonacci" : "Factorial", rank, rank % 2 ? fib(rank) : fact(rank));
    MPI_Finalize();
    return 0;
}

