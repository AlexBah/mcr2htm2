/* 	C;	create index.htm from *.mcr */
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <string.h>
// move to library
void HeadMaker (FILE *pTextFile)
{
    fprintf(pTextFile, "<HTML>\n");
    fprintf(pTextFile, "<HEAD>\n");
    fprintf(pTextFile, "<TITLE>\n");
    fprintf(pTextFile, "</TITLE>\n");
    fprintf(pTextFile, "</HEAD>\n");
    fprintf(pTextFile,  
	"<body bgcolor=#ffffff text=#000000 link=#000000 vlink=#000000 alink=#000000>\n");
    fprintf(pTextFile, "<font face=Arial size=2>\n");
}
int SeekFile(char *ShortName, char *Extension)
{
	struct _finddata_t Picture_file;
	intptr_t pFile;
	// push name and extension of file  to FullNamePicture
	char FullNamePicture[100] = "";
	strcpy(FullNamePicture, ShortName);
	strcat(FullNamePicture, ".");
	strcat(FullNamePicture, Extension);
	// try seek file
	if ((pFile = _findfirst(FullNamePicture, &Picture_file)) == -1L)
		{
		_findclose(pFile); //close seeking
		return 1; // not found
		}
	else
	{
		_findclose(pFile); //close seeking
		return 0; // found
	}
}
void DivMaker (FILE *pTextFile,char *FileName)
{
	//push to ShortName name of "*.mcr" without extension
	char ShortName[100] = "";
	strncpy(ShortName, FileName, strlen(FileName) - 4);
	// begining of <div> block
	fprintf(pTextFile, "<Div style=\"float:left; width:120px; height:160px; overflow:hidden\">\n");
	fprintf(pTextFile, "	<a href=\"%s.mcr\">\n", ShortName);
	// Image of *.mcr
	if (SeekFile(ShortName, "jpg") == 0)
		fprintf(pTextFile, "		<img src=\"%s.jpg\" width=100 height=100 border=0 \n", ShortName);
	else
	{
		if (SeekFile(ShortName, "gif") == 0)
			fprintf(pTextFile, "		<img src=\"%s.gif\" width=100 height=100 border=0 \n", ShortName);
		else
		{
			if (SeekFile(ShortName, "png") == 0)
				fprintf(pTextFile, "		<img src=\"%s.png\" width=100 height=100 border=0 \n", ShortName);
			else
			{
				if (SeekFile(ShortName, "bmp") == 0)
					fprintf(pTextFile, "		<img src=\"%s.bmp\" width=100 height=100 border=0 \n", ShortName);
			}
		}
	}
	// end of <div> block
    fprintf(pTextFile, "		ALT=\"%s\">\n", ShortName);
    fprintf(pTextFile, "		<br>%s<br></a>\n", ShortName);
    fprintf(pTextFile, "</Div>\n");
}
// move to library
void BottomMaker (FILE *pTextFile)
{
	fprintf(pTextFile, "<Div style=\"float:top; width:120px; height:120px;\">\n");
    fprintf(pTextFile, "	<br><a href=\"index.htm\">Обновить страницу</a>\n");
    // call that files, not recurse
	fprintf(pTextFile, "	<a href=\"mcr2htm2.exe\">Обновить блоки</a>\n");
    fprintf(pTextFile, "</Div>\n");
    fprintf(pTextFile, "</BODY></HTML>\n");
	fclose(pTextFile);
}
int main(void)
{
	// try create index.htm
	FILE *pTextFile = fopen("index.htm", "w");
    if(pTextFile == NULL)
		{
        return EXIT_FAILURE;
		}
	// Write head to index.htm
	HeadMaker(pTextFile);
	// Seek first "*.mcr"
    struct _finddata_t c_file; //c_files - "*.mcr" file
    intptr_t hFile;
    if( (hFile = _findfirst( "*.mcr", &c_file )) == -1L )
		printf( "No *.mcr files in current directory!\n" );
		else
		{ do { 	
			DivMaker (pTextFile, c_file.name);// Write block <div> to index.htm
			} while( _findnext( hFile, &c_file ) == 0 );// Seek next "*.mcr"
		_findclose( hFile ); //close seeking
		}
	BottomMaker(pTextFile);
	// Write bottom to index.htm
	return EXIT_SUCCESS;
}
