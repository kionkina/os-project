CC=g++

CFLAGS= -c
objects: main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o

prog: main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o
	$(CC) main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o -o prog

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o prog

