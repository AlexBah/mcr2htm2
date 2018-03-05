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
// make div definitly heght
void DivMaker (FILE *pTextFile,char *FileName)
{
	char s1[100] = "";
	strncpy(s1, FileName, strlen(FileName) - 4 );
	fprintf(pTextFile, "<Div style=\"float:left; width:120px; height:160px;\">\n");
    fprintf(pTextFile, "	<a href=\"%s.mcr\">\n", s1 );
    fprintf(pTextFile, "		<img src=\"%s.jpg\" width=100 height=100 border=0 \n", s1);
    fprintf(pTextFile, "		ALT=\"%s\">\n", s1);
    fprintf(pTextFile, "		<br>%s<br></a>\n", s1);
    fprintf(pTextFile, "</Div>\n");
}
// move to library
void BottomMaker (FILE *pTextFile)
{
	fprintf(pTextFile, "<Div style=\"float:top; width:120px; height:120px;\">\n");
    fprintf(pTextFile, "	<br><a href=\"index.htm\">Обновить страницу</a>\n");
    fprintf(pTextFile, "	<a href=\"mcr2htm2.exe\">Обновить блоки</a>\n");
    fprintf(pTextFile, "</Div>\n");
    fprintf(pTextFile, "</BODY></HTML>\n");
	fclose(pTextFile);
}
int main(void)
{
    FILE *pTextFile = fopen("index.htm", "w");
    if(pTextFile == NULL)
		{
        return EXIT_FAILURE;
		}
	HeadMaker(pTextFile);
    struct _finddata_t c_file;
    intptr_t hFile;
    if( (hFile = _findfirst( "*.mcr", &c_file )) == -1L )
		printf( "No *.mcr files in current directory!\n" );
		else
		{ do {
			DivMaker (pTextFile, c_file.name);
			} while( _findnext( hFile, &c_file ) == 0 );
		_findclose( hFile );
		}
	BottomMaker(pTextFile);
	return EXIT_SUCCESS;
}