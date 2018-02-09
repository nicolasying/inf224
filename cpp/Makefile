##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du SERVERramme
#
SERVER = server

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#

SERVER_SOURCES = photo.cpp video.cpp multim.cpp group.cpp film.cpp main.cpp cppsocket.cpp tcpserver.cpp db.cpp
#
# Fichiers objets (ne pas modifier sauf si l'extension n'est pas .cpp)
#
OBJETS = ${SERVER_SOURCES:%.cpp=%.o}

#
# Compilateur C++
#
CXX = c++

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Exemple: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CXXFLAGS = -std=c++11 -Wall -O

#
# Options de l'editeur de liens
#
LDFLAGS =

#
# Librairies a utiliser
# Exemple: LDLIBS = -L/usr/local/qt/lib -lqt
#
LDLIBS = -lpthread


##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${SERVER} sera un fichier contenant les dependances
#

all: 
	make ${SERVER}

run: ${SERVER} 
	./${SERVER} 3333


run-deserial: ${SERVER}
	./${SERVER} 3333 ../src/serial.out
 

${SERVER}: depend-${SERVER} ${OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o depend-${SERVER} core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${SERVER} 1>/dev/null 2>&1

tar:
	tar cvf ${SERVER}.tar.gz ${SERVER_SOURCES}

# Gestion des dependances : creation automatique des dependances en utilisant
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${SERVER}:
	${CXX} ${CXXFLAGS} -MM ${SERVER_SOURCES} > depend-${SERVER}


###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c (CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${SERVER}
