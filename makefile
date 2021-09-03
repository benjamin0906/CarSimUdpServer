CC=gcc
UTILITIES_DIR=Utilities
SHARED_DIR=Shared

IDIR=-I.
IDIR+=-I Utilities
IDIR+=-I Shared

SOURCE=
SOURCE+=main.c
SOURCE+=CommThread/CommThread.c
SOURCE+=$(UTILITIES_DIR)/Utilities.c
SOURCE+=$(SHARED_DIR)/Shared.c
CFLAG=-lpthread
build:
	$(CC) $(CFLAG) -o CarSimUdpServer $(SOURCE) $(IDIR)
