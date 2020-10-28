#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
typedef struct{
    _Bool a_case;
    _Bool t_case;
    int filecount;
    int dircount;
    char** filenames;
    int notFound;
    _Bool errors;
}structCases;

structCases options(int argc, char* argv[]);
void reset(structCases* cases);
char** lexographicalSort (int filecount, char** filenames);
char** timeSorting (int filecount, char** filenames, char* dirName);
int dirContents(structCases cases);
char* getPath(char* filename, char* dirName, char arr[]);