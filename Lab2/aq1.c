#include<mpi.h>
#include<stdio.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main(int argc, char* argv[]){
    int size, rank, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int arr[5] = {10, 15, 3, 7, 9};
    MPI_Scatter(arr, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(isPrime(num))
        printf("Process %d: %d is prime\n", rank, num);
    else
        printf("Process %d: %d is not prime\n", rank, num);
    MPI_Finalize();
    return 0;
}