#On spécifie ici le chemin des codes sources (*.c) et des bibliothèques (*.h)
SRC = src/
INCL = inc/

inc = -I./inc 


#Voici tous les fichiers du projet (*.o)
PROJET = MakerDoc.o Html.o Css.o Main.o ModifFile.o Ensemble.o
#le nom de l'exécutable
EXEC = docmycode

#Voici les informations concernant le compilateur
FLAGS = -Wall -ansi -g -pedantic
CC = gcc

#Voici la règle de compilation 
$(EXEC) : $(PROJET)
	@echo "Création de l'exécutable -> $@"
	@$(CC) $(FLAGS) $(PROJET) $(lib) -o $@

#Ici on trouve la règle de compilation générique des objets
%.o : $(SRC)%.c $(INCL)%.h
	@echo "Création de l'objet $@"
	@$(CC) $(FLAGS) $(inc) -c $< -o $@

#Règle pour supprimer l'exécutable et les .o (fichiers objets)
clean :
	@rm -f $(EXEC) *.o