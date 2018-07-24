#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int id; /* Process rank */
    int p;  /* Number of processes */
    int next_proc, prev_proc;
    float to_recv, to_send, local_sum;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &p); //attempted to test for 0 input (won't work)
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    next_proc = (id + 1) % p;

    if (!id)
    {
        prev_proc = p - 1;
        local_sum = id;
        if (p == 1)
        {
            MPI_Finalize();

            printf("%d : %1.f\n", id, local_sum);

            return 0;
        }
        MPI_Sendrecv(&to_send, 1, MPI_FLOAT, next_proc, 0, &to_recv, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &status);
        local_sum += to_recv;

        MPI_Sendrecv(&to_send, 1, MPI_FLOAT, prev_proc, 0, &to_recv, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &status);
        local_sum += to_recv;

        printf("%d : %1.f\n", id, local_sum); //print val
    }
    else
    {
        prev_proc = id - 1;
        to_send = id;
        local_sum = id;

        MPI_Sendrecv(&to_send, 1, MPI_FLOAT, prev_proc, 0, &to_recv, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &status);
        local_sum += to_recv;

        MPI_Sendrecv(&to_send, 1, MPI_FLOAT, next_proc, 0, &to_recv, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &status);
        local_sum += to_recv;

        printf("%d : %1.f\n", id, local_sum); //print val
    }

    MPI_Finalize();

    return 0;
}
