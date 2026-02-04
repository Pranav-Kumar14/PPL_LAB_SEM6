#include<mpi.h>
#include<stdio.h>
#include<ctype.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char str[] = "HELLO";
    char ch;
    MPI_Scatter(str, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(islower(ch)){
        ch = toupper(ch);
    }
    else{
        ch = tolower(ch);
    }
    MPI_Gather(&ch, 1, MPI_CHAR, str, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("Toggled String : %s\n", str);
    }
    MPI_Finalize();
    return 0;
}