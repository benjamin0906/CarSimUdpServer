CC=gcc
IDIR +=.
SOURCE+=\
	main.c\
	CommThread/CommThread.c
CFLAG=-lpthread
build:
	$(CC) $(CFLAG) -o CarSimUdpServer $(SOURCE) -I $(IDIR)
