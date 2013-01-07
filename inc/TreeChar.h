#ifndef TREECHAR_H
#define TREECHAR_H

#include <stdio.h>

/**
 * \file      TreeChar.c
 * \author    Fuhs
 * \author    Moreau
 * \version   3.0
 * \date      11 Décembre 2012
 * \brief     Functions helping to manage the analysis on the tree of the project
 *
 * Library which contains functions of manipulation of tree, for the files of the project.
 */

struct list A;

typedef struct
{
	char* name;
	struct list * children;
} TreeChar;

typedef struct list
{
	TreeChar* element;
	struct list * next;	
}*List;

/**
 * \fn         TreeChar* allocate(char* name)
 * \brief	   Function which creates a new tree in the memory.
 * \param      name	is the name of the root repository.
 * \return     A pointer on the tree which will contain the files of the project.
 */
TreeChar* allocate(char* name);

/**
 * \fn         void free_TreeChar(TreeChar * tree)
 * \brief	   Function which release a tree.
 * \param      tree is the tree to free.
 */
void free_TreeChar(TreeChar * tree);

/**
 * \fn         void free_list(struct list* list)
 * \brief	   Function which release a list.
 * \param      list is the list to free.
 */
void free_list(List list);

/**
 * \fn         void add_child(char* name, struct list** liste)
 * \brief	   Function which add a tree to a list.
 * \param      list is the list to free.
 * \param		name is the name of the repository to add in the tree and then in the list.
 */
void add_child(char* name, struct list** list);

/**
 * \fn         void AddSubTree(TreeChar* node, char* buffer, int pos_buff)
 * \brief	   Add all the subrepository and files in the tree which the root is the root repository.
 * \param      node	is the node which contain the root repository.
 * \param		buffer	is the path of the current repository.
 * \param		pos_buff	is a position in the buffer.
 */
void AddSubTree(TreeChar* node, char* buffer, int pos_buff);


/**
 * \fn         TreeChar* CreateTree(char* root)
 * \brief	   Function which create a tree.
 * \param      root	is the path of the root repository of the project.
 * \return		A pointer on the new Tree created.
 */
TreeChar* CreateTree(char* root);

/**
 * \fn         void print_TreeChar(FILE* file, TreeChar* tree, int rang)
 * \brief	   Print a tree in a file.
 * \param      file	is a pointer on the file which the tree has to be written on.
 * \param		tree	is the tree to print in the file.
 * \param		rang	is the rank of the repository/file in the tree
 */
void print_TreeChar(FILE* file, TreeChar* tree, int rang);

/**
 * \fn         int path_file(const TreeChar* tree, char* file_search, char* buff,int pos_buff)
 * \brief		Give the path of a file in the tree.
 * \param      	tree	is the tree which contains all the files and repository.
 * \param		file_search		is the name of the file to search in the tree.
 * \param		buff	will be the path of the file searched.
 * \param		pos_buff	is a position in the buffer.
 * \return		An integer which is a special exit code.
 */
int path_file(const TreeChar* tree, char* file_search, char* buff,int pos_buff);

#endif
