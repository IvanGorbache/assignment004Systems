#include "compress.h"

struct _fourBitNum
{
    unsigned int _data:  4;
}typedef fourBitNum;

void compress(const char* filePath)
{
    FILE *fptr, *binfptr;
    char *binaryOutFile = malloc(((strlen(filePath)+1) * sizeof(char))), ch; 
    unsigned char compressed = 0;
    int cursor = 4;
    fourBitNum code;

    strcpy(binaryOutFile,filePath);
    binaryOutFile[strlen(binaryOutFile)-3] = 'b';
    binaryOutFile[strlen(binaryOutFile)-2] = 'i';
    binaryOutFile[strlen(binaryOutFile)-1] = 'n';

    fptr = fopen(filePath, "r");
    binfptr = fopen(binaryOutFile,"wb");
    

    while((ch=fgetc(fptr))!=EOF && ch != '\n' && ch != '\r')
    {
        if (ch >= '0' && ch <= '9') {
            code._data = ~(ch - '0');
            compressed |= (code._data<<cursor);
            cursor-=4;
            
            if(cursor<0)
            {
                fwrite(&compressed, sizeof(unsigned char), 1, binfptr);
                compressed = 0;
                cursor = 4;
            }
        }
    }
    
    if(cursor == 0)
    {
        fwrite(&compressed, sizeof(unsigned char), 1, binfptr);
    }
    


    fclose(fptr);
    fclose(binfptr);
    free(binaryOutFile);
}

void decompress(const char* filePath)
{
    FILE *fptr, *binfptr;
    char *textOutFile = malloc((strlen(filePath) + 1) * sizeof(char));
    fourBitNum code;
    unsigned char compressed = 0;
    int cursor = 0;
    
    strcpy(textOutFile, filePath);
    textOutFile[strlen(textOutFile)-3] = 't';
    textOutFile[strlen(textOutFile)-2] = 'x';
    textOutFile[strlen(textOutFile)-1] = 't';

    fptr = fopen(textOutFile, "w");
    binfptr = fopen(filePath, "rb");

    while (fread(&compressed, sizeof(unsigned char), 1, binfptr) == 1) {
        compressed = ~compressed;
        for(int i = 0;i<2;i++)
        {
            code._data = (compressed >> 4) & 0x0F;
            compressed <<= 4;
            
            if(code._data!=15)
            {
                fprintf(fptr,"%c",code._data+'0');
            }
        }

    }

    fclose(fptr);
    fclose(binfptr);
    free(textOutFile);
}