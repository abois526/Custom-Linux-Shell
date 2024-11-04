#----------- ID HEADER -------------------------------------
#  Author(s):	Andrew Boisvert, Kyle Scidmore
#  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.cas
#  File Name:   makefile
#
#  Program Purpose(s):
#    To help determine what parts of the program need to be
#    recompiled, and to aid in the process of doing so.
#-----------------------------------------------------------

#--------- Variable declarations ---------------------------
# Targets and objects
TARGET=mysh
OBJECTS=signals.o parse.o stringlib.o prompt.o memory.o jobs.o commands.o mysh.o

# CC stuff
CC=gcc
CFLAGS=-g


#--------- Building, Linking, Cleaning ---------------------
# Building the target
all: clean $(TARGET)

# Linking target executable from object files
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Cleaning up the old object files and executable
clean:
	rm -f *.o $(TARGET)


#--------- Creating Object Files --------------------------- 
mysh.o: mysh.c commands.h jobs.h memory.h prompt.h stringlib.h parse.h signals.h globals.h errorcodes.h
	$(CC) $(CFLAGS) -c mysh.c 

commands.o: commands.c commands.h errorcodes.h memory.h prompt.h
	$(CC) $(CFLAGS) -c commands.c 

jobs.o: jobs.c jobs.h globals.h errorcodes.h stringlib.h
	$(CC) $(CFLAGS) -c jobs.c 

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c 

parse.o: parse.c parse.h jobs.h commands.h globals.h stringlib.h
	$(CC) $(CFLAGS) -c parse.c

prompt.o: prompt.c prompt.h stringlib.h
	$(CC) $(CFLAGS) -c prompt.c 

stringlib.o: stringlib.c stringlib.h 
	$(CC) $(CFLAGS) -c stringlib.c

signals.o: signals.c signals.h 
	$(CC) $(CFLAGS) -c signals.c
# The empty line above this comment must remain to avoid errors