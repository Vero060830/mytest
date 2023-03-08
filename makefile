
# code details


EXE    = pgmEcho
SRC =  pgmEcho.c read_file.c write_file.c     
OBJ =  pgmEcho.o read_file.o write_file.o    


   

# generic build details

CC     = gcc
CFLAGS = -std=c99 -Wall
CLIBS  = 
CLINK  = 

# compile to object code

%.o: %.c
	$(CC) -c $(CFLAGS) $(CLIBS) $< -o $@

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) 

# dependencies

#
# ** put code dependencies here **
#
