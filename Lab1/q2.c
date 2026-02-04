#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int a = 50, b = 10;
    if(rank==0) printf("a+b : %d\n", a+b);
    else if(rank==1) printf("a-b : %d\n", a-b);
    else if(rank==2) printf("a*b : %d\n", a*b);
    else if(rank==3) printf("a/b : %d\n", a/b);
    MPI_Finalize();
    return 0;
}