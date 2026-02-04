#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[]){
    int size, rank;
    char word[20] = "HelloWorld";
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0){
        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(word, 20, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received: %s\n", word);
    }
    else{
        MPI_Recv(word, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; word[i]; i++) {
            if (islower(word[i]))
                word[i] = toupper(word[i]);
            else
                word[i] = tolower(word[i]);
        }
        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}