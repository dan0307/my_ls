#include "headers.h"
#include <stdio.h>
void reset(structCases* cases){ 
    cases->a_case = 0;
    cases->t_case = 0;
    cases->filecount = 1;
    cases->dircount = 1;
    cases->filenames = malloc(sizeof(char*));
    cases->filenames[0] = ".";
    cases->errors = 0;
    cases->notFound = 0;
}
structCases options(int argc, char* argv[]){
    struct stat statStruct;
    structCases cases;
    reset(&cases);
    int i, statReturn,errorCount = 0, countfile = 0, dircount = 0;
    for(i = 1; i<argc; i++){
        if (argv[i][0] == '-'){     //detect options
            switch (argv[i][1]){
                case 'a':
                    cases.a_case = 1;
                    break;
                case 't':
                    cases.t_case = 1;
                    break;
                default:
                    printf("my_ls: invalid option -- '%c'\n", argv[i][1]);
                    cases.errors = 1;   // end the program after 
                    break;
            }
        }else{      // detect filenames
            statReturn = stat(argv[i], &statStruct);    //returns 0 if success, also fills in the statStruct 
            if(statReturn!=0){
                errorCount++;
                printf("my_ls: cannot access '%s': No such file or directory\n", argv[i]);
            }else{
                if (countfile == 0){
                    free(cases.filenames);
                    cases.filenames = malloc(sizeof(char*)* (argc-1));
                }
                if(S_ISDIR(statStruct.st_mode)){    //count directories
                    dircount++;
                }
                cases.filenames[countfile++] = argv[i];
            }
        }
    }
    cases.notFound=errorCount;
    if(countfile == 0 && errorCount!=0){    
        cases.errors = 1;   // if all arguments are not found 
    }
    if(cases.errors){
        free(cases.filenames);
    }
    if(countfile>1){    
        if(cases.t_case){
            timeSorting(countfile, cases.filenames, ".");   //if -t option - sort by time modified
        }else{
            lexographicalSort(countfile,cases.filenames);
        }
        cases.filecount = countfile;
        cases.dircount =dircount;
    }
    return cases;   
}
int stringCompare(char* a, char*b){
    for(int i = 0; *a!='\0'|| *b!= '\0';i++, *a++, *b++){
        if(*a < *b ){
            return 1;
        }
        if(*a>*b){
            return 2;
        }
    }
    return 0;
}
int my_strlen(char* arr){
    int i;
    for(i = 0; arr[i]!= '\0';i++){

    }
    return i;
}

char* getPath(char* filename, char* dirName, char arr[]){   //sets name with path of directory and the file in it
    int i = 0;
    for(int j = 0; dirName[j]!= '\0'; j++){
        arr[i++] = dirName[j];
    }
    arr[i++] = '/';
    for(int j = 0;filename[j]!='\0';j++){
        arr[i++] = filename[j];
    }
    arr[i] = '\0';
    return &arr[0];
}
char** lexographicalSort (int filecount, char** filenames){     //sort by ASCII 
    _Bool isSorted;     
    int i;
    char* temp;
    while(!isSorted){   //stops when all elements of the array are sorted
        isSorted = 1;
        for(i = 0;i<filecount-1;i++){
            if(stringCompare(filenames[i], filenames[i+1])==2){
                temp = filenames[i];
                filenames[i] = filenames[i+1];
                filenames[i+1] = temp;
                isSorted = 0; 
            }
        }
    }
    return filenames;
}

char** timeSorting (int filecount, char** filenames, char* dirName){    //sort by last time modified
    struct stat statStruct1;    
    struct stat statStruct2;
    _Bool isSorted = 0;
    char arr[100];
    int i, k, l; 
    char* temp;
    while(!isSorted){
        isSorted = 1;
        for(i = 0; i<filecount-1; i++){
            temp = getPath(filenames[i], dirName, arr);
            k = stat(temp, &statStruct1);   //to get the last time modified
            temp = getPath(filenames[i+1], dirName, arr);
            l = stat(temp, &statStruct2);
            if(statStruct1.st_mtim.tv_sec<statStruct2.st_mtim.tv_sec){
                temp = filenames[i];
                filenames[i] = filenames[i+1];
                filenames[i+1] = temp;
                isSorted = 0; 
            }

            else if(statStruct1.st_mtim.tv_sec==statStruct2.st_mtim.tv_sec){
                if(statStruct1.st_mtim.tv_nsec<statStruct2.st_mtim.tv_nsec){
                    temp = filenames[i];
                    filenames[i] = filenames[i+1];
                    filenames[i+1] = temp;
                    isSorted = 0; 
                }
                else if(statStruct1.st_mtim.tv_nsec==statStruct2.st_mtim.tv_nsec){
                    if(stringCompare(filenames[i], filenames[i+1])==2){
                        temp = filenames[i];
                        filenames[i] = filenames[i+1];
                        filenames[i+1] = temp;
                        isSorted = 0; 
                    }
                }
            }
        }
    }
    return filenames;
}