#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){
    int size, rank, x = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    long pow = 1;
    for(int i=1; i<=rank; i++) pow*=x;
    printf("Rank %d Power of 10: %ld\n", rank, pow);
    printf(rank%2==0?"Hello\n":"World\n");
    MPI_Finalize();
    return 0;
}