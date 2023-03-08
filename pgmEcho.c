/***********************************/
/* XJCO 1921M Programming Project  */
/* 2022-23 Spring Semester         */
/*           			   */
/*                                 */
/* Version 0.2: Zheng Wang         */
/* Version 0.1: Hamish Carr        */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in ASCII and echo the data */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>
#include <stdlib.h>
#include"file_info.h"
#include "read_file.h"
#include"write_file.h"
#include"pgm_error.h"

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	Info *info=NULL; //a structure to store the information of the file
	if (argc != 3)	
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */
	char *infile=argv[1];
	char *outfile=argv[2];
	int  value=EXIT_NO_ERRORS;
	int *returnValue=&value;
	//read the data from the file
	info=read_file(info,infile,returnValue); 
	if (*returnValue==0){
		 info=write_file(info,outfile,returnValue);
	}
	//write the data into a file

   
	/* at this point, we are done and can exit with a success code */
	return *returnValue;
} /* main() */
