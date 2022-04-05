all: pere fils

pere: pere.c fonction_bases.o
	@echo "Compilation du pere ..."
	@gcc $^ -o pere

fils: fils.c fonction_bases.o
	@echo "Compilation du fils ..."
	@gcc $^ -o $@

fonction_bases.o: fonction_bases.c
	@echo "Compilation des fonctions de base ..."
	@gcc -c $<

.PHONY = clean

clean:
	@echo "Suppression des fichiers objets et executables ..."
	@rm *.o pere fils out/*
