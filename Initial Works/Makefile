CC = mpicc
PROG = send-recv isend-irecv reduce sndrcv

all:	$(PROG)

isend-irecv:	isend-irecv.o
	$(CC) $< -o $@

isend-irecv.o:	isend-irecv.c
	$(CC) -c $< -o $@

send-recv:	send-recv.o
	$(CC) $< -o $@

send-recv.o:	send-recv.c
	$(CC) -c $< -o $@

reduce:	reduce.o
	$(CC) $< -o $@

reduce.o:	reduce.c
	$(CC) -c $< -o $@

sndrcv:	sndrcv.o
	$(CC) $< -o $@

sndrcv.o:	sndrcv.c
	$(CC) -c $< -o $@

clean:
	rm -f $(PROG) *.o *~ core
