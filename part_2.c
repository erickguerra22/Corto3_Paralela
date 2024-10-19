#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 5000

int main(int argc, char *argv[]) {
    int rank, size;
    int local_array[LENGTH], global_sum, global_max, global_prod;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    for (int i = 0; i < LENGTH; i++) {
        local_array[i] = rand() % 100;
    }

    MPI_Reduce(local_array, &global_sum, LENGTH, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    MPI_Reduce(local_array, &global_max, LENGTH, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    
    MPI_Reduce(local_array, &global_prod, LENGTH, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Suma: %d\n", global_sum);
        printf("Max: %d\n", global_max);
        printf("Producto: %d\n", global_prod);
    }

    MPI_Finalize();
    return 0;
}
