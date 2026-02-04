#include <mpi.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isVowel(char c) {
    c = tolower(c);
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}

int main(int argc, char *argv[]) {
    int rank, size, chunk;
    char str[100], local[20];
    int local_count = 0, counts[10], total = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter string: ");
        scanf("%s", str);
        chunk = strlen(str) / size;
    }
    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, chunk, MPI_CHAR, local, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < chunk; i++)
        if (!isVowel(local[i]))
            local_count++;
    MPI_Gather(&local_count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("Process %d non-vowels = %d\n", i, counts[i]);
            total += counts[i];
        }
        printf("Total non-vowels = %d\n", total);
    }
    MPI_Finalize();
    return 0;
}
