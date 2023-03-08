#include <stdio.h>
#include <stdlib.h>
#include"file_info.h"
#include "read_file.h"
#include"pgm_error.h"

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

Info* write_file(Info *info,char* outfile,int * returnValue)
{  
	long nImageBytes = info->width * info->height * sizeof(unsigned char);

	/* open a file for writing               */
	FILE *outputFile = fopen(outfile, "w");
   
	/* check whether file opening worked     */
	if (outputFile == NULL)
	{ /* NULL output file */
		/* free memory                   */
		free(info->commentLine);
		free(info->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed %s",outfile);	
		/* return an error code          */
		* returnValue=EXIT_OUTPUT_FAILED;
		return NULL;
	} /* NULL output file */
//
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", info->width, info->height, info->maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
	{ /* dimensional write failed    */
		/* free memory                   */
		free(info->commentLine);
		free(info->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed %s", outfile);	

		/* return an error code          */
		* returnValue=EXIT_OUTPUT_FAILED;
		return NULL;
	} /* dimensional write failed    */


	/* pointer for efficient write code      */
	for (unsigned char *nextGrayValue = info->imageData; nextGrayValue < info->imageData + nImageBytes; nextGrayValue++)
	{ /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - info->imageData + 1) % info->width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
		{ /* data write failed   */
			/* free memory           */
			free(info->commentLine);
			free(info->imageData);

			/* print error message   */
			printf("ERROR: Output Failed %s", outfile);	

			/* return an error code  */
		* returnValue=EXIT_OUTPUT_FAILED;
		return NULL;
		} /* data write failed   */
	} /* per gray value */
	

}

