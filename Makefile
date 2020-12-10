CC=g++-10

CFLAGS= -c -Wall
objects: main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o

#-c flag says don't try to create an executable, but just compile it to an object file
#all: prog

# TODO: figure out why $(objects) is ahjfkdjhfla
prog: main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o
	$(CC) main.o OperatingSystem.o PCB.o ReadyQueue.o Disk.o HardDisk.o RAM.o -o prog

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o prog

