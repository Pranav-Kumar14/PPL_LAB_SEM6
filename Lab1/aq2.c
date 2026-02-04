#include <mpi.h>
#include <stdio.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        printf("Primes from 1 to 50:\n");
        for (int i = 1; i <= 50; i++)
            if (isPrime(i)) printf("%d ", i);
        printf("\n");
    } else if (rank == 1) {
        printf("Primes from 51 to 100:\n");
        for (int i = 51; i <= 100; i++)
            if (isPrime(i)) printf("%d ", i);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
