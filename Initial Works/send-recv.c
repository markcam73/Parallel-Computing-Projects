#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
  int id;               /* Process rank */
  int p;                /* Number of processes */
  int next_proc, prev_proc;
  float to_send, to_recv;
  struct MPI_Status status;

  MPI_Init (&argc, &argv);

  MPI_Comm_size (MPI_COMM_WORLD, &p); //attempted to test for 0 input (won't work)
  MPI_Comm_rank (MPI_COMM_WORLD, &id);

  next_proc = (id + 1)%p;

  if(!id)
  {
    prev_proc = p - 1;
    to_send = 0;
    to_recv = 0;
    if(p == 1)
    {
        MPI_Finalize();

        printf("%1.f\n",to_send);
        printf("%1.f\n",to_recv);

        return 0;
    }
    MPI_Send(&to_send,1,MPI_FLOAT,next_proc,0,MPI_COMM_WORLD);
    MPI_Send(&to_send,1,MPI_FLOAT,prev_proc,0,MPI_COMM_WORLD);
    MPI_Recv(&to_recv,1,MPI_FLOAT,prev_proc,0,MPI_COMM_WORLD,&status); //recv from prev_proc
    printf("%1.f\n",to_recv); //print val
    MPI_Recv(&to_recv,1,MPI_FLOAT,next_proc,0,MPI_COMM_WORLD,&status); //recv from next_proc
    printf("%1.f\n",to_recv); //print val
  }else{
    prev_proc = id - 1;
    MPI_Recv(&to_recv,1,MPI_FLOAT,prev_proc,0,MPI_COMM_WORLD,&status); //recv from prev_proc
    to_send = to_recv + id;
    MPI_Send(&to_send,1,MPI_FLOAT,next_proc,0,MPI_COMM_WORLD); //send to next_proc
    
    MPI_Recv(&to_recv,1,MPI_FLOAT,next_proc,0,MPI_COMM_WORLD,&status); //recv from next_proc
    to_send = to_recv - id;
    MPI_Send(&to_send,1,MPI_FLOAT,prev_proc,0,MPI_COMM_WORLD); //send to prev_proc

  }

  MPI_Finalize();

  return 0;
}
