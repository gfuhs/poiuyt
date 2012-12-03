#include "Ensemble.h"
#include <stdlib.h>
#include <string.h>

/**
 * \fn         int AddEnsemble(ListEns* list, char *name)
 * \brief      Add a file set to an existing list. 
 * \param      list	is a pointer on the list already existing
 * \param		name is a string which contains the key words.
 * \return     An integer which is an output code.
 */
int AddEnsemble(ListEns* list, char *name)
{
		ListEns tmp;
		int size;
		
		if( (tmp = (ListEns) malloc (sizeof(Ens)) ) == NULL)
		{
			return 0;
		}

		tmp->file[0] = '\0';			
		strcpy(tmp->file, "doc/");
		strcat(tmp->file, name);
		size = strlen(tmp->file);
		tmp->file[size - 1] = '\0';	
		strcat(tmp->file, "html\0");
	   	
		tmp->path_file_c[0] = '\0';			
		strcpy(tmp->path_file_c, "src/");
		strcat(tmp->path_file_c, name);
		size = strlen(tmp->path_file_c);
		tmp->path_file_c[size - 1] = 'c';
		tmp->path_file_c[size] = '\0';	
	
		tmp->path_file_h[0] = '\0';			
		strcpy(tmp->path_file_h, "inc/");
		strcat(tmp->path_file_h, name);
		size = strlen(tmp->path_file_h);
		tmp->path_file_h[size - 1]='h';
		tmp->path_file_h[size] = '\0';
	   
		tmp->next = *list;
		*list = tmp;
		
		return 1;		
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
