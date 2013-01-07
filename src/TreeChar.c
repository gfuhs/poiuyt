#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "TreeChar.h"
#include "Html.h"

TreeChar* allocate(char* name)
{
	char * tmp_name;
	TreeChar * tmp_tree;
	
	if( (tmp_tree = (TreeChar *) malloc(sizeof(TreeChar))) == NULL)
	{
		return NULL;
	}
		
	if( (tmp_name = (char*) malloc(sizeof(char) * (strlen(name) + 1))) == NULL )
	{
		fprintf(stderr, "Erreur allocation mémoire\n");
		free(tmp_tree);
		exit(1);;
	}
	
	strcpy(tmp_name, name);
	tmp_tree->name = tmp_name;
	tmp_tree->children = NULL;
	return tmp_tree;
}

void free_TreeChar(TreeChar * tree)
{
	if(tree == NULL)
	{
		return;
	}
		
	free_list(tree->children);
	free(tree->name);
	free(tree);
	tree = NULL;	
}

void free_list(struct list* liste)
{
	List index;
	
	while(liste != NULL)
	{	
		index = liste;
		liste = liste->next;
		free_TreeChar(index->element);			
	}
}

void add_child(char* name, struct list** liste)
{
	List tmp;
	
	if( (tmp = (struct list*) malloc(sizeof(struct list))) == NULL)
	{
		fprintf(stderr, "Erreur lors de la création de l'arborescence\n");
		exit(1);	
	}
	
	tmp->element = allocate(name);
	tmp->next = *liste;
	*liste = tmp;
}

void AddSubTree(TreeChar* node, char* buffer, int pos_buff)
{
	DIR *dh;
	struct dirent *f;

	/*Ouverture du dossier courant*/
	if( (dh = opendir(buffer)) == NULL)
	{
		return;
	}
	
	/*Parcours de celui ci*/
	do 
	{
		if( (f = readdir(dh)) != NULL)
		{
			buffer[pos_buff] = '\0';
			add_child(f->d_name, &(node->children));
							
			if( (strchr(f->d_name, '.')) == NULL) 
			{
				strcat(buffer, "/\0");
				strcat(buffer, f->d_name);
				AddSubTree(node->children->element, buffer, strlen(buffer));
			}
		}
	}
	while(NULL != f);
	
	closedir(dh);
}

TreeChar* CreateTree(char * root)
{
	int pos_buff;
	char buffer[1024];
	TreeChar * tree;	
	DIR *dh;
	struct dirent * f;
	
	buffer[0] = '\0';
	strcat(buffer, root);
	strcat(buffer, "/\0");
	pos_buff = strlen(buffer);
	
	if(NULL == (dh = opendir(root))) 
	{
		fprintf(stderr, "Impossible d'ouvrir le répertoire contenant le projet\n" );
		exit(1);	
	}
	
	tree = allocate(root);
	
	do 
	{
		if(NULL != (f = readdir(dh)))
		{
				add_child(f->d_name, &(tree->children));
				
				if((strchr(f->d_name, '.')) == NULL)
				{				  
					strcat(buffer,f->d_name);
					AddSubTree(tree->children->element, buffer,pos_buff);
					buffer[pos_buff]= '\0';
				}
		}
	}
	while(NULL != f);
	
	closedir(dh);
	return tree;
}


void print_TreeChar(FILE* file, TreeChar* tree, int rank)
{
	List index;
	
	if(tree == NULL)
	{
		return;
	}
	
	putTab(file, rank-1);
	
	newBalise(file, -2, NULL);
	
	if(strstr(tree->name, ".") != NULL)
	{
		if(strstr(tree->name, ".c") != NULL && tree->name[strlen(tree->name) - 1] == 'c')
		{
			newBalise(file, 14, tree->name);
		}
		
		if(strstr(tree->name, ".h") != NULL && tree->name[strlen(tree->name) - 1] == 'h')
		{
			newBalise(file, 14, tree->name);
		}
		
		if(strstr(tree->name, "./") != NULL)
		{
			newBalise(file, 13, tree->name);
		}
	}
	
	else
	{
		newBalise(file, 13, tree->name);
	}
	
	for(index = tree->children; index != NULL; index = index->next)
	{
		print_TreeChar(file, index->element, rank + 1);	
	}
	
	newBalise(file, -3, NULL);
}

int path_file(const TreeChar* tree, char* file_search, char* buff, int pos_buff)
{
	int taille;
	List index;
		
	if(tree == NULL)
	{
		return 0;
	}

	buff[pos_buff] = '\0';
	strcat(buff + pos_buff, tree->name);
	
	if(strcmp(file_search, tree->name) == 0)
	{
		return 1;
	}		
		
	strcat(buff, "/\0");
	taille = strlen(buff);
	
	for(index = tree->children; index != NULL ; index = index->next)
	{
		if(path_file(index->element, file_search, buff, taille))
		{
			return 1;
		}
	}
	
	return 0;
}
