#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"stdbool.h"
#include"main.h"

int main(int argc, char *argv[])
{
    char *outdir = ".";
    for(int i = 1; i < argc; i++)
    {
        printf("arg[%i]: %s\n", i, argv[i]);

        if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-output") == 0)
        {
            outdir = argv[i + 1];
            i++;
            printf("output dir set to: %s\n", outdir);
        }
        else
        {
            processFile(argv[i], outdir);
        }
    } 
    return 0;
}

bool debug = false;

void processFile(char *fname, char *outdir)
{
    printf("processing file: %s with output: %s\n", fname, outdir);

    FILE* inputf = fopen(fname, "r");

    if(!inputf)
    {
        printf("error opening file: %s\n", fname);
        return;
    }

    char *end = strrchr(fname, '.');
    *end ='\0';
    char *tempf = strrchr(fname, '/');
    if(tempf)
    {
        fname = tempf + 1;
    }
    createOutput(outdir,fname);

    char ch;
    bool inHead = true;
    while((ch = fgetc(inputf)) != EOF)
    {
        if(debug)
            printf("c: %c\n", ch);

        if(ch == '#')
        {
            char *next = malloc(sizeof(char) * 5); 
            fgets(next, 5, inputf);
            if(strcmp(next, "sour") == 0)
            {
                printf("printing to source now!\n");
                inHead = false;
                while((ch = fgetc(inputf)) != '\n'){}
            }
            else if(strcmp(next, "head") == 0)
            {
                printf("printing to head now!\n");
                inHead = true;
                while((ch = fgetc(inputf)) != '\n'){}
            }
            else
            {
                if(inHead)
                {
                    fputc(ch, headf);
                    fputs(next, headf);
                }
                else
                {
                    fputc(ch, sourcef);
                    fputs(next, sourcef);

                }
            }
            free(next);
        } 
        else
        {
            if(inHead)
            {
                fputc(ch, headf);
            }
            else
            {
                fputc(ch, sourcef);
            }
        }
    }

    closeFiles();
}

FILE *headf = NULL;
FILE *sourcef = NULL;

bool createOutput(char *outdir, char *file)
{
    printf("creating files fname: %s outputdir: %s\n", file, outdir);
    char *head = malloc(sizeof(char) * (strlen(outdir) + strlen(file) + 4));
    char *source = malloc(sizeof(char) * (strlen(outdir) + strlen(file) + 4));

    strcpy(head, outdir);
    strcat(head, "/");
    strcat(head, file);
    strcat(head, ".h\0");

    strcpy(source, outdir);
    strcat(source, "/");
    strcat(source, file);
    strcat(source, ".c\0");

    printf("source: %s\n", source);
    printf("head: %s\n", head);

    headf = fopen(head, "w+");
    sourcef = fopen(source, "w+");

    free(head);
    free(source);

    if(!headf || !sourcef)
    {
        printf("error creating head and source files!\n");
    }
    return true;
}

bool closeFiles()
{
    fclose(headf);
    fclose(sourcef);
    return true;
}
