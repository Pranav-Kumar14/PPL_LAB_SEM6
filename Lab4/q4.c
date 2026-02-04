#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char ch;
    char str[100], local[50], result[200];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter string: ");
        fflush(stdout);
        scanf("%s", str);
        int pos = 0;
        result[pos++] = str[0];
        for (int i = 1; i < size; i++)
            MPI_Send(&str[i], 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        for (int i = 1; i < size; i++) {
            MPI_Recv(local, i + 1, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < i + 1; j++)
                result[pos++] = local[j];
        }
        result[pos] = '\0';
        printf("Result = %s\n", result);
    }
    else {
        MPI_Recv(&ch, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i <= rank; i++)
            local[i] = ch;
        MPI_Send(local, rank + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
