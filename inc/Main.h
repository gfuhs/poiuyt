#ifndef MAIN_H
#define MAIN_H

/**
 * \file      Main.c
 * \author    Fuhs
 * \author    Moreau
 * \version   3.0
 * \date      11 Décembre 2012
 * \brief     Define the main function of the program.
 *
 * This function run the program and manage the arguments on the command line
 */
 
/**
 * \fn         int main(int argc, char* argv[])
 * \brief      Main function of the program.
 * \param      argc	number of arguments on the command line.
 * \param      argv	Table of the arguments of the command line.
 * \return     An integer which is a special exit code.
 */
 int main(int argc, char* argv[]);
 
 void method_file_pass_argument(int argc, char * argv[]);
 
 void method_path_project(char * path);
 
 #endif
