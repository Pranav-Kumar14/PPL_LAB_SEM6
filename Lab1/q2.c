#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a = 20, b = 5;
    int r = rank%4;
    if(r==0)
        printf("Rank %d: %d + %d = %d\n", rank, a, b, a + b);
    else if(r==1)
        printf("Rank %d: %d - %d = %d\n", rank, a, b, a - b);
    else if(r==2)
        printf("Rank %d: %d * %d = %d\n", rank, a, b, a * b);
    else
        printf("Rank %d: %d / %d = %d\n", rank, a, b, a / b);
    MPI_Finalize();
    return 0;
}