#include "compress.h"

#define ARG_NUM 

int main (int argc, char *argv[]){
    if(argc == 3)
    {
        char flag = argv[1][1];
        char* filePath = argv[2];

        switch (flag)
        {
        case 'c':
            compress(filePath);
            break;

        case 'd':
            decompress(filePath);
            break;
        
        default:
            break;
        }
    }
    return 0;
}