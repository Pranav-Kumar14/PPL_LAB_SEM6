#include<mpi.h>
#include<stdio.h>

int fact(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

int sum(int n) {
    return (n * (n + 1)) / 2;
}

int main(int argc, char* argv[]){
    int size, rank;
    int value = 0, result;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank % 2 == 0)
        value = fact(rank + 1);
    else
        value = sum(rank + 1);
    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("Final Result: %d\n", result);
    }
    MPI_Finalize();
    return 0;
}