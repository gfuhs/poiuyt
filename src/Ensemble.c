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
 * \return     An integer which is an output code.
 */
int AddEnsemble(ListEns* list, char *name, const TreeChar* tree)
{
		ListEns tmp;
		int size;
		char* tmp_name;
		
		if((tmp= (ListEns)malloc(sizeof(Ens))) == NULL)
			return 0;
		if((tmp_name=(char*)malloc(sizeof(char)*strlen(name)+1)) == NULL)
		{
		  free(tmp);
		  return 0;
		}
		
	 
	   tmp->file[0]='\0';			
	   strcpy(tmp->file,"doc/");
	   strcat(tmp->file,name);
	   size=strlen(tmp->file);
	   tmp->file[size-1]='\0';	
	   strcat(tmp->file,"html\0");
	   	
	   tmp->path_file_c[0]='\0';			
	   tmp_name[0]='\0';
	   strcpy(tmp_name,name);
	   size=strlen(tmp_name);
	   tmp_name[size-1]='c';tmp_name[size]='\0';
	   if( path_file(tree,tmp_name,tmp->path_file_c,0) == 0 )
	   {
	     free(tmp);
	     free(tmp_name);
	     return 0;
	   }
	   
	   tmp_name[size-1]='h';
	   if( path_file(tree,tmp_name,tmp->path_file_h,0) == 0 )
	   {
	     free(tmp);
	     free(tmp_name);
	     return 0;
	   }	   
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
		return 0;
		
	*list=(*list)->next;
	free(tmp);
	return 1;	
}