#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <sys/types.h>

void handle_fdata(struct _finddata_t *pfdata, char *currdir, char *cmd)
{
    char cmd_ctx[2048];
    char drive[64];
    char dir[2048];
    char fname[512];
    char ext[64];
    char cmd_path[2048];
    char *fileext;

    _splitpath(cmd, drive, dir, fname, ext);
    sprintf(cmd_path, "%s\"%s\"", drive, dir);

    switch(pfdata->attrib)
    {
    case _A_SUBDIR:
        if(strcasecmp(pfdata->name, ".") == 0||
           strcasecmp(pfdata->name, "..") == 0||
           strcasecmp(pfdata->name, ".git") == 0||
           strcasecmp(pfdata->name, ".svn") == 0)
        {
            break;
        }
        sprintf(cmd_ctx, "%s%s%s \"%s\\%s\"",cmd_path, fname, ext, currdir, pfdata->name);
        system(cmd_ctx);
        printf("test system return\n");
        break;
    default:
        fileext = strrchr(pfdata->name, '.');
        if(strcasecmp(fileext, ".o") == 0||
                strcasecmp(fileext, ".crf") == 0||
                strcasecmp(fileext, ".dep") == 0||
                strcasecmp(fileext, ".d") == 0||
                strcasecmp(fileext, ".exe") == 0||
                strcasecmp(fileext, ".a") == 0||
                strcasecmp(fileext, ".dll") == 0||
                strcasecmp(fileext, ".lib") == 0||
                strcasecmp(fileext, ".so") == 0||
                strcasecmp(fileext, ".rar") == 0||
                strcasecmp(fileext, ".zip") == 0||
                strcasecmp(fileext, ".7z") == 0||
                strcasecmp(fileext, ".gz") == 0||
                strcasecmp(fileext, ".xz") == 0||
                strcasecmp(fileext, ".iso") == 0||
                strcasecmp(fileext, ".img") == 0||
                strcasecmp(fileext, ".tar") == 0)
        {
            break;
        }
        if(strcasecmp(fileext, ".png") == 0||
                strcasecmp(fileext, ".bmp") == 0||
                strcasecmp(fileext, ".jpg") == 0||
                strcasecmp(fileext, ".jpeg") == 0||
                strcasecmp(fileext, ".gif") == 0)
        {
            sprintf(cmd_ctx, "%smspaint.exe \"%s\\%s\"", cmd_path, currdir, pfdata->name);
        }
        else if(strcasecmp(fileext, ".pcbdoc") == 0||
                        strcasecmp(fileext, ".prjpcb") == 0||
                        strcasecmp(fileext, ".schdoc") == 0)
        {
            sprintf(cmd_ctx, "%sdxp.exe \"%s\\%s\"", cmd_path, currdir, pfdata->name);
        }
        else
        {
            sprintf(cmd_ctx, "%sjavaw.exe \"%s\\%s\"", cmd_path, currdir, pfdata->name);
        }
        system(cmd_ctx);
        //printf("systemJavaw: %s\n",cmd_ctx);
        break;
    }
}
void check_sub_path(char *currdir, char *cmd)
{
    struct _finddata_t fdata;
    long fd;
    char firstdir[2048];

    sprintf(firstdir, "%s\\*", currdir);
    fd = _findfirst(firstdir, &fdata);
    handle_fdata(&fdata, currdir, cmd);
    while(_findnext(fd, &fdata) == 0)
    {
        handle_fdata(&fdata, currdir, cmd);
    }
}


int main(int argc, char *argv[])
{
    char cmdpath[2048];
    char cmd_ctx[2048];
    struct _finddata_t filedata;
    int i;
    long fd;

    char drive[64];
    char dir[2048];
    char fname[512];
    char ext[64];
    char *fileext;

    _splitpath(argv[0], drive, dir, fname, ext);
    sprintf(cmdpath, "%s\"%s\"", drive,dir);
    for(i = 1; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
        fd = _findfirst(argv[i], &filedata);
        {
            switch(filedata.attrib)
            {
            case _A_SUBDIR:
                check_sub_path(argv[i], argv[0]);
                break;
            default:
                fileext = strrchr(filedata.name, '.');
                if(strcasecmp(fileext, ".o") == 0||
                strcasecmp(fileext, ".crf") == 0||
                strcasecmp(fileext, ".dep") == 0||
                strcasecmp(fileext, ".d") == 0||
                strcasecmp(fileext, ".exe") == 0||
                strcasecmp(fileext, ".a") == 0||
                strcasecmp(fileext, ".dll") == 0||
                strcasecmp(fileext, ".lib") == 0||
                strcasecmp(fileext, ".so") == 0||
                strcasecmp(fileext, ".rar") == 0||
                strcasecmp(fileext, ".zip") == 0||
                strcasecmp(fileext, ".7z") == 0||
                strcasecmp(fileext, ".gz") == 0||
                strcasecmp(fileext, ".xz") == 0||
                strcasecmp(fileext, ".iso") == 0||
                strcasecmp(fileext, ".img") == 0||
                strcasecmp(fileext, ".tar") == 0)
                {
                    break;
                }
                if(strcasecmp(fileext, ".png") == 0||
                        strcasecmp(fileext, ".bmp") == 0||
                        strcasecmp(fileext, ".jpg") == 0||
                        strcasecmp(fileext, ".jpeg") == 0||
                        strcasecmp(fileext, ".gif") == 0)
                {
                    sprintf(cmd_ctx, "%smspaint.exe \"%s\"", cmdpath, argv[i]);
                }
                else if(strcasecmp(fileext, ".pcbdoc") == 0||
                        strcasecmp(fileext, ".prjpcb") == 0||
                        strcasecmp(fileext, ".schdoc") == 0)
                {
                    sprintf(cmd_ctx, "%sdxp.exe \"%s\"", cmdpath, argv[i]);
                }
                else
                {
                    sprintf(cmd_ctx, "%sjavaw.exe \"%s\"", cmdpath, argv[i]);
                }
                system(cmd_ctx);
                break;
            }
        }

        while(_findnext(fd, &filedata) == 0)
        {
            switch(filedata.attrib)
            {
            case _A_SUBDIR:
                check_sub_path(argv[i], argv[0]);
                break;
            default:
                fileext = strrchr(filedata.name, '.');
                if(strcasecmp(fileext, ".o") == 0||
                strcasecmp(fileext, ".crf") == 0||
                strcasecmp(fileext, ".dep") == 0||
                strcasecmp(fileext, ".d") == 0||
                strcasecmp(fileext, ".exe") == 0||
                strcasecmp(fileext, ".a") == 0||
                strcasecmp(fileext, ".dll") == 0||
                strcasecmp(fileext, ".lib") == 0||
                strcasecmp(fileext, ".so") == 0||
                strcasecmp(fileext, ".rar") == 0||
                strcasecmp(fileext, ".zip") == 0||
                strcasecmp(fileext, ".7z") == 0||
                strcasecmp(fileext, ".gz") == 0||
                strcasecmp(fileext, ".xz") == 0||
                strcasecmp(fileext, ".iso") == 0||
                strcasecmp(fileext, ".img") == 0||
                strcasecmp(fileext, ".tar") == 0)
                {
                    break;
                }
                if(strcasecmp(fileext, ".png") == 0||
                        strcasecmp(fileext, ".bmp") == 0||
                        strcasecmp(fileext, ".jpg") == 0||
                        strcasecmp(fileext, ".jpeg") == 0||
                        strcasecmp(fileext, ".gif") == 0)
                {
                    sprintf(cmd_ctx, "%smspaint.exe \"%s\"", cmdpath, argv[i]);
                }
                else if(strcasecmp(fileext, ".pcbdoc") == 0||
                        strcasecmp(fileext, ".prjpcb") == 0||
                        strcasecmp(fileext, ".schdoc") == 0)
                {
                    sprintf(cmd_ctx, "%sdxp.exe \"%s\"", cmdpath, argv[i]);
                }
                else
                {
                    sprintf(cmd_ctx, "%sjavaw.exe \"%s\"", cmdpath, argv[i]);
                }
                system(cmd_ctx);
                break;
            }
        }
    }
    //system("pause");
    return 0;
}
