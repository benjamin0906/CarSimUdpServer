CC=gcc
UTILITIES_DIR=Utilities

IDIR=-I.
IDIR+=-I Utilities

SOURCE+=\
	main.c\
	CommThread/CommThread.c\
	$(UTILITIES_DIR)/Utilities.c
CFLAG=-lpthread
build:
	$(CC) $(CFLAG) -o CarSimUdpServer $(SOURCE) $(IDIR)
