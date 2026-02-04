#include <mpi.h>
#include <stdio.h>

int fact(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

void handle_mpi_error(int error_code) {
    if (error_code != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length, error_class;
        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_code, error_string, &length);
        fprintf(stderr, "MPI Error Class: %d\nMPI Error: %s\n", error_class, error_string);
        MPI_Abort(MPI_COMM_WORLD, error_code);
    }
}

int main(int argc, char *argv[]) {
    int rank, size, local, scan_sum;
    int err;
    MPI_Init(&argc, &argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    handle_mpi_error(err);
    err = MPI_Comm_size(MPI_COMM_WORLD, &size);
    handle_mpi_error(err);
    local = fact(rank + 1);
    err = MPI_Scan(&local, &scan_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    handle_mpi_error(err);
    if (rank == size - 1)
        printf("Result = %d\n", scan_sum);
    MPI_Finalize();
    return 0;
}
