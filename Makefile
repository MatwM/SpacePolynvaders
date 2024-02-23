#==========================================
#                 Makefile
#==========================================

CC := gcc
# Liste des répertoires conta -lSDL2_ttenant respectivement les fichiers :*.cpp,*.h,*.o, l'exécutable
SRCDIR := ./src_C
BINDIR := ./bin

CFLAGS := -g -Wall
GLLIBS := $(sdl2-config --cflags --libs) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lmpg123 -lm
 
# L'exécutable
BIN := game
# Où trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

all: $(BIN)
# Création de l'exécutable
$(BIN): $(OBJ)
	@echo "=== Checking ==="
	$(CC) -o $@ $^ $(CFLAGS) $(GLLIBS)
# Création des différents *.o à partir des *.c
$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo "=== Creating object ==="
	$(CC) -o $@ -c $< $(CFLAGS)
# Nettoyage des objets (Tout sera recompiler)
clean:
	@echo "=== Cleaning up ==="
	rm $(BINDIR)/*.o
