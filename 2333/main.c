#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <direct.h>
#include <time.h>


extern void Init2333(void);
extern char *fcontent[];
    static clock_t curr, old;
int delay (void)
{
    curr = clock();
    while(curr - old < 50)
    {
        curr = clock();
    }
    old = curr;
    return 0;
}

int main(int argc, char* argv[])
{
    FILE *frp=NULL;
    FILE *fwp=NULL;
    uint32_t rb;
    uint8_t ctx[2048];
    char topath[2048];
    char fullpath[2048];
    char renamepath[2048];
    char cmdpath[2048];

    char drive[64];
    char dir[2048];
    char fname[512];
    char ext[64];

    int i;
    //sprintf(cmdpath, "\"%s\"", argv[0]);
    _splitpath(argv[0], drive, dir, fname, ext);
    sprintf(cmdpath, "%s\"%s\"", drive,dir);

    for(i = 1; i < argc; i++)
    {
        //sprintf(topath, "\"%s\"", argv[i]);
        _splitpath(argv[i], drive, dir, fname, ext);
        sprintf(topath, "%s%s",drive,dir);

        frp = fopen(argv[i], "rb+");
        sprintf(fullpath, "%s%s%s.rgw",topath,fname,ext);
        fwp = fopen(fullpath, "wb+");
        do
        {
            rb = fread(ctx, 1, 2048, frp);
            fwrite(ctx, 1, rb, fwp);
        }
        while(rb != 0);
        fclose(frp);
        fclose(fwp);
        sprintf(renamepath, "%s%s%s", topath, fname,ext);
        unlink(renamepath);
        sprintf(renamepath, "%s6666.exe \"%s\"", cmdpath, fullpath);
        system(renamepath);
    }
    return 0;
}
