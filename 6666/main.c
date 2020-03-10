#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char drive[64];
    char dir[2048];
    char fname[512];
    char ext[64];

    char renamepath[2048];
    int i;
    for(i = 1; i < argc; i++)
    {
        //sprintf(renamepath, "\"%s\"", argv[i]);
        _splitpath(argv[i], drive, dir, fname, ext);
        sprintf(renamepath, "%s%s%s", drive, dir, fname);
        rename(argv[i], renamepath);
    }
    return 0;
}
