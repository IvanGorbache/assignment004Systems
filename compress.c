#include "compress.h"

void compress(const char* filePath)
{
    FILE *fptr, *binfptr;
    char *code = malloc(1000 * sizeof(char)), 
    *binaryOutFile = malloc(((strlen(filePath)+1) * sizeof(char)));

    fptr = fopen(filePath, "r");
    int ch, index = 0;
    while ((ch = fgetc(fptr)) != EOF && index < 1000) {
        // Perform bitwise NOT operation on the character
        code[index++] = ~(char)ch;
    }
    code[index] = '\0';
    fclose(fptr);

    strcpy(binaryOutFile,filePath);
    binaryOutFile[strlen(binaryOutFile)-3] = 'b';
    binaryOutFile[strlen(binaryOutFile)-2] = 'i';
    binaryOutFile[strlen(binaryOutFile)-1] = 'n';

    binfptr = fopen(binaryOutFile,"wb");
    fwrite(code, sizeof(char), strlen(code), binfptr);

    fclose(binfptr);
    free(code);
    free(binaryOutFile);
}

void decompress(const char* filePath)
{
    FILE *fptr, *binfptr;
    char *textOutFile = malloc((strlen(filePath+1) * sizeof(char)));
    unsigned char *buffer = malloc(1000 * sizeof(unsigned char));

    binfptr = fopen(filePath, "rb");
    fread(buffer,sizeof(buffer),1,binfptr);

    fclose(binfptr);

    strcpy(textOutFile,filePath);
    textOutFile[strlen(textOutFile)-3] = 't';
    textOutFile[strlen(textOutFile)-2] = 'x';
    textOutFile[strlen(textOutFile)-1] = 't';

    fptr = fopen(textOutFile,"w");
    for(int i = 0;i<strlen(buffer);i++)
    {
        fputc(~buffer[i], fptr);
    }
    fclose(fptr);
    free(buffer);
    free(textOutFile);
}