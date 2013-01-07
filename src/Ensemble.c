#include "Ensemble.h"
#include <stdlib.h>
#include <string.h>
#include "TreeChar.h"

/**
 * \fn         int AddEnsemble(ListEns* list, char *name)
 * \brief      Add a file set to an existing list. 
 * \param      list	is a pointer on the list already existing
 * \param		name is a string which contains the key words.
 * \param		tree is the arborescence of project
 * \param		path is the way acces of project
 * \return     An integer which is an output code.
 */
int AddEnsemble(ListEns* list, char *name, const TreeChar* tree, char* path)
{
	int size;
	char * tmp_name;
	ListEns tmp;
	
	if( (tmp = (ListEns) malloc(sizeof(Ens))) == NULL)
	{
		return 0;
	}
	
	if( (tmp_name = (char*) malloc(sizeof(char) * (strlen(name) + 1))) == NULL)
	{
		free(tmp);
		return 0;
	}
	
 
	tmp->file[0] = '\0';			
	strcpy(tmp->file, path);
	strcat(tmp->file, "doc/");
	strcat(tmp->file, name);
	size = strlen(tmp->file);
	tmp->file[size - 1]= '\0';	
	strcat(tmp->file, "html\0");
	
	tmp->path_file_c[0] = '\0';			
	tmp_name[0] = '\0';
	strcpy(tmp_name, name);
	size = strlen(tmp_name);
	tmp_name[size - 1] = 'c';
	tmp_name[size] = '\0';
	
	if( path_file(tree, tmp_name, tmp->path_file_c, 0) == 0 )
	{
		free(tmp);
		free(tmp_name);
		return 0;
	}
   
	tmp_name[size - 1] = 'h';
	tmp->path_file_h[0] = '\0';
	
	if( path_file(tree, tmp_name, tmp->path_file_h, 0) == 0 )
	{
		free(tmp);
		free(tmp_name);
		return 0;
	}	   
  
	tmp->next = *list;
	*list = tmp;
	return 1;		
}

/*******
 ******* \fn	void GenerateEnsemble(ListEns* list, const TreeChar* tree, const TreeChar* node, char* path)
  ****** \brief	generate a List of Listens from a TreeChar
   ***** \param	list is a pointer of  the list to do
    **** \param	tree is the root of the tree which will be listed.
     *** \param	node is the current node of the tree.
      ** \param	path is the way of acces to the root of the tree in the system arborescence
       */ 
void GenerateEnsemble(ListEns* list,const TreeChar* tree,const TreeChar* node, char* path)
{
	struct list* index;
		
	if(node == NULL)
	{
		return;
	}

	if(strstr(node->name, ".c") != NULL && node->name[strlen(node->name) - 1] == 'c')
	{		
		if(AddEnsemble(list, node->name, tree, path)==0)
		{
			fprintf(stderr, "Erreur lors de la récupération d'un fichier dans l'arborescence %s\n", node->name);
			exit(1);
		}		
	}	
	
	for(index = node->children; index != NULL; index = index->next)
	{
		GenerateEnsemble(list,tree,index->element,path);
	}
}	

/**
 * \fn         int RemoveEnsemble(ListEns* list)
 * \brief      Remove the head of the list. 
 * \param      list	is a pointer on the list to modify
 * \return     An integer which is an output code.
 */
int RemoveEnsemble(ListEns* list)
{
	ListEns tmp = *list;
	
	if(*list == NULL)
	{
		return 0;
	}
		
	*list = (*list)->next;
	free(tmp);
	return 1;	
}
