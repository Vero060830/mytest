
typedef struct file_info{
	unsigned short *magic_Number;
	char *commentLine ;
	unsigned char magic_number[2];
	unsigned int width,height;
	unsigned int maxGray;
	unsigned char *imageData;	
}Info;
