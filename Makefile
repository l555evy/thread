#makefile
gcc=cc

thread1: thread1.o
	cc -o thread1 thread1.o -pthread
thread2: thread2.o
	cc -o thread2 thread2.o -pthread
thread3: thread3.o
	cc -D_REENTRANT -o thread3 thread3.o -pthread
clean: 
	rm -rf thread1 thread2 thread3 *.o
