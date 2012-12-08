#ifndef TREECHAR_H
#define TREECHAR_H

#include <stdio.h>

struct list A;

typedef struct
{
	char* name;
	struct list * children;
} TreeChar;

struct list
{
	TreeChar* element;
	struct list * next;	
};


TreeChar* allocate(char* name);
void free_TreeChar(TreeChar * tree);
void free_list(struct list* liste);
void add_child(char* name, struct list** liste);
void AddSubTree(TreeChar* node, char* buffer, int pos_buff);
TreeChar* CreateTree(char* root);
void print_TreeChar(FILE* file, TreeChar* tree, int rang);
int path_file(const TreeChar* tree, char* file_search, char* buff,int pos_buff);

#endif
