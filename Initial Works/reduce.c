#include <stdio.h>
#include <unistd.h>
#include <mpi.h>


int main (int argc, char *argv[]) 
{
  int id;               /* Process rank */
  int p;                /* Number of processes */
  float to_send, to_recv;

  MPI_Init (&argc, &argv);

  MPI_Comm_size (MPI_COMM_WORLD, &p); //attempted to test for 0 input (won't work)
  MPI_Comm_rank (MPI_COMM_WORLD, &id);

  if(!id)
  {
    if(p == 1)
    {
        MPI_Finalize();

        printf("%1.f\n",to_send);
        printf("%1.f\n",to_recv);

        return 0;
    }
    MPI_Reduce(&to_send, &to_recv,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD); //recv first sum
    printf("%1.f\n",to_recv); //print val

    MPI_Reduce(&to_send, &to_recv,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD); //recv second sum
    printf("%1.f\n",to_recv); //print val
  }else{

    to_send = id;
    MPI_Reduce(&to_send, &to_recv,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

    to_send = -1 * id;
    MPI_Reduce(&to_send, &to_recv,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}