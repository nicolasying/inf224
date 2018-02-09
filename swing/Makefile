##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

CLIENT = Remote

CLIENT_SOURCES = Remote.java
JC = javac
FLAGS = -Wall -O

all: 
	make ${CLIENT}

run: ${CLIENT}
	java ${CLIENT} localhost 3333

${CLIENT}: 
	javac ${CLIENT_SOURCES}

clean:
	-@$(RM) *.class

