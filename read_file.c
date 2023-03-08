#include <stdio.h>
#include <stdlib.h>
#include"file_info.h"
#include "read_file.h"
#include"pgm_error.h"

#define MAGIC_NUMBER_RAW_PGM 0x3550 //
#define MAGIC_NUMBER_ASCII_PGM 0x3250 //
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128
Info* read_file(Info * info,char* infile,int * returnValue)
{   
    info=(Info *)malloc(sizeof(Info));
    if(NULL==info) { // judge whether there is insufficient space
        *returnValue=MISCELLANEOUS;
        printf("ERROR: Info Structure Malloc Failed");
		return NULL;
    }
	unsigned char magic_number[2] = {'0','0'};
	unsigned short *magic_Number = (unsigned short *) magic_number;
	char *commentLine = NULL;
	unsigned int width = 0, height = 0;
	unsigned int maxGray = 255;
	unsigned char *imageData = NULL;
    
	FILE *inputFile = fopen(infile, "r");
	/* if it fails, return error code        */
	if (inputFile == NULL){
		*returnValue=EXIT_BAD_FILE_NAME;
		printf("ERROR: Bad File Name %s",infile);
		return NULL;
    } 
	/* read in the magic number              */
	magic_number[0] = getc(inputFile);
	magic_number[1] = getc(inputFile);
    
	/* sanity check on the magic number      */
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
	{ /* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number %s", infile);	
	 
		/* and return                    */
		
		* returnValue=EXIT_BAD_MAGIC_NUMBER;
		return NULL;

	} /* failed magic number check   */

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
	{ /* comment line                */
		/* allocate buffer               */
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		if (commentLine == NULL)
	{ /* malloc failed */
		/* free up memory                */
		free(commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Commentline Malloc Failed ");	
        
		/* return error code             */
		* returnValue=MISCELLANEOUS;
		return NULL;
	} /* malloc failed */
		
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
		{ /* NULL comment read   */
			/* free memory           */
			free(commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Bad Comment Line %s", infile);	
		
			/* and return            */
			* returnValue=EXIT_BAD_COMMENT_LINE;
		return NULL;
		} /* NULL comment read   */
	} /* comment line */
	else
	{ /* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);
	} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
			(width 	< MIN_IMAGE_DIMENSION	) 	||
			(width 	> MAX_IMAGE_DIMENSION	) 	||
			(height < MIN_IMAGE_DIMENSION	) 	||
			(height > MAX_IMAGE_DIMENSION	) 
		)
	{ /* failed size sanity check    */
		/* free up the memory            */
		free(commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Dimensions %s", infile);	
		/* and return                    */
		
		* returnValue=EXIT_BAD_DIMENSIONS;
		return NULL;
	} /* failed size sanity check    */
	if 	(maxGray	!= 255		)
	{ /* failed size sanity check    */
		/* free up the memory            */
		free(commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value %s", infile);	
		/* and return                    */
		
		* returnValue=EXIT_BAD_MAX_GRAY_VALUE;
		return NULL;
	} /* failed size sanity check    */






	/* allocate the data pointer             */
	long nImageBytes = width * height * sizeof(unsigned char);
	imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (imageData == NULL)
	{ /* malloc failed */
		/* free up memory                */
		free(commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Image Malloc Failed ");	
        
		/* return error code             */
		* returnValue=EXIT_IMAGE_MALLOC_FAILED;
		return NULL;
	} /* malloc failed */

	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
	{ /* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		/* sanity check	                 */
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ /* fscanf failed */
			/* free memory           */
			free(commentLine);
			free(imageData);	

			/* close file            */
			fclose(inputFile);

			/* print error message   */
			printf("ERROR: Bad Data %s", infile);	
			/* and return            */
		* returnValue=EXIT_BAD_DATA;
		return NULL;
		} /* fscanf failed */

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
	} /* per gray value */
  
    info->width=width;
    info->height=height;
    info->maxGray=maxGray;
    info->commentLine=commentLine;
    info->magic_number[0]=magic_number[0];
    info->magic_number[0]=magic_number[1];
    info-> imageData=imageData;
	/* we're done with the file, so close it */
	fclose(inputFile);
	return info;
}
