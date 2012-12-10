#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "TreeChar.h"

TreeChar* allocate(char* name)
{
	TreeChar* tmp_tree;
	char* tmp_name;
	if((tmp_tree=(TreeChar*)malloc(sizeof(TreeChar))) == NULL)
		return NULL;
		
	if( (tmp_name=(char*)malloc(sizeof(char)*strlen(name)+1)) == NULL )
	{
		free(tmp_tree);
		fprintf(stderr,"Erreur allocation mémoire\n");
		exit(1);;
	}
	
	strcpy(tmp_name,name);
	tmp_tree->name = tmp_name;
	tmp_tree->children = NULL;
	return tmp_tree;
}

void free_TreeChar(TreeChar * tree)
{
	if(tree == NULL) 
		return ;
		
	free_list(tree->children);
	free(tree->name);
	free(tree);
	tree=NULL;	
}

void free_list(struct list* liste)
{
	struct list* index;
	while (liste != NULL)
	{	
		index = liste;
		liste=liste->next;
		free_TreeChar(index->element);			
	}
}

void add_child(char* name, struct list** liste)
{
	struct list* tmp;
	
	if((tmp=(struct list*)malloc(sizeof(struct list))) == NULL)
	{
		fprintf(stderr,"Erreur lors de la création de l'arborescence\n");
		exit(1);	
	}
	
	tmp->element = allocate(name);
	tmp->next = *liste;
	*liste = tmp;
}

void AddSubTree(TreeChar* node,char* buffer,int pos_buff)
{
	DIR *dh;
	struct dirent *f;


	if((dh=opendir(buffer))==NULL) 
			return ;
	
	do 
	{
		if((f = readdir(dh)) != NULL)
		{
				buffer[pos_buff]='\0';
				add_child(f->d_name,&(node->children));				
				if ((strchr(f->d_name, '.')) == NULL) 
				{
				  strcat(buffer,"/\0");
				  strcat(buffer,f->d_name);
				  AddSubTree(node->children->element,buffer,strlen(buffer));
				}
		}
	}while(NULL != f);
	closedir(dh);
}

TreeChar* CreateTree(char* root)
{
	TreeChar* tree;	
	DIR *dh;
	struct dirent *f;
	char buffer[1024];
	int pos_buff;
	
	buffer[0]='\0';
	strcat(buffer,root);
	strcat(buffer,"/\0");
	pos_buff = strlen(buffer);
	
	if(NULL == (dh=opendir(root))) 
	{
		fprintf(stderr,"Impossible d'ouvrir le répertoire contenant le projet\n" );
		exit(1);	
	}
	
	tree= allocate(root);
	
	do 
	{
		if(NULL != (f = readdir(dh)))
		{
				add_child(f->d_name,&(tree->children));
				if ((strchr(f->d_name, '.')) == NULL)
				{				  
				  strcat(buffer,f->d_name);
				  AddSubTree(tree->children->element,buffer,pos_buff);
				  buffer[pos_buff]='\0';
				}
		}
	}while(NULL != f);
	
	closedir(dh);
	return tree;
}

void print_TreeChar(FILE* file, TreeChar* tree, int rang)
{
	struct list* index;
	int i;
	
	if(tree == NULL)
		return;
	
	for(i=0;i<rang;i++)
		fprintf(file,"\t");
	fprintf(file,"%s\n",tree->name);
	
	for(index= tree->children;index!=NULL;index=index->next)
			print_TreeChar(file,index->element,rang+1);	
		
}

int path_file(const TreeChar* tree, char* file_search, char* buff,int pos_buff)
{
		struct list* index;
		int taille;
		
		if(tree==NULL)
		  return 0;

		buff[pos_buff]='\0';
		strcat(buff+pos_buff,tree->name);
		if(strcmp(file_search,tree->name) == 0)
				return 1;
		
		if(pos_buff != 0)
		  strcat(buff,"/\0");
		taille = strlen(buff);
		for (index=tree->children;index!=NULL;index=index->next)
			if(path_file(index->element,file_search,buff,taille))
				return 1;
		return 0;
}