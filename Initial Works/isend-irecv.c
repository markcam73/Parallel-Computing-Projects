#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#define TOT_REQUEST 4 //max number of requests each process makes
#define TOT_STATUS  4 //max number of status's that are returned
int main(int argc, char *argv[])
{
    int id; /* Process rank */
    int p;  /* Number of processes */
    int next_proc, prev_proc;
    float to_send, to_recv;
    MPI_Status status[TOT_STATUS]; //array to store status
    MPI_Request request[TOT_REQUEST]; //array to store requests

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &p); //attempted to test for 0 input (won't work)
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    next_proc = (id + 1) % p;

    if (!id)
    {
        prev_proc = p - 1;
        to_send = 0;
        to_recv = 0;
        if (p == 1)
        {
            MPI_Finalize();

            printf("%1.f\n", to_send);
            printf("%1.f\n", to_recv);

            return 0;
        }
        MPI_Isend(&to_send, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &request[0]);
        MPI_Isend(&to_send, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &request[1]);
        MPI_Waitall(2, request, status); //wait for sends

        MPI_Irecv(&to_recv, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &request[0]); //recv from prev_proc
        MPI_Waitall(1, request, status); //wait for value to come back
        printf("%1.f\n", to_recv); //print val

        MPI_Irecv(&to_recv, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &request[0]); //recv from next_proc
        MPI_Waitall(1, request, status); //wait for value to come back
        printf("%1.f\n", to_recv); //print val
    }
    else
    {
        prev_proc = id - 1;

        MPI_Irecv(&to_recv, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &request[0]); //recv from prev_proc
        MPI_Waitall(1, request, status); //wait for value to come back

        to_send = to_recv + id;
        MPI_Isend(&to_send, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &request[0]);

        MPI_Irecv(&to_recv, 1, MPI_FLOAT, next_proc, 0, MPI_COMM_WORLD, &request[1]); //recv from next_proc
        MPI_Waitall(2, request, status); //wait for value to come back

        to_send = to_recv - id;
        MPI_Isend(&to_send, 1, MPI_FLOAT, prev_proc, 0, MPI_COMM_WORLD, &request[0]); //send to prev_proc
    }

    MPI_Finalize();

    return 0;
}