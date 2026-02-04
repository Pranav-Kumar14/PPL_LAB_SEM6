#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    int size, rank;
    int *arr, val;
    void* buffer;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    buffer = malloc(1024);
    MPI_Buffer_attach(buffer, 1024);
    if(rank==0){
        arr = (int*)malloc(size * sizeof(int));
        for(int i=0; i<size; i++){
            arr[i] = i+1;
        }
        for(int i=0; i<size; i++){
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (rank % 2 == 0)
            printf("Process %d square = %d\n", rank, val * val);
        else
            printf("Process %d cube = %d\n", rank, val * val * val);
    }
    MPI_Buffer_detach(&buffer, &size);
    MPI_Finalize();
    return 0;
}