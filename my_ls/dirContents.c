#include "stdio.h"
#include "headers.h"
int dirContents(structCases cases){
    int i;
    struct stat statStruct;
    char** dirContentfiles = malloc(1000);
    for(i = 0; i<cases.filecount; i++){     //first, output all nondirectories
        stat(cases.filenames[i],&statStruct);
        if(S_ISDIR(statStruct.st_mode)){
            continue;
        }
        else{
            printf("%s\n\n", cases.filenames[i]);
        }
    }
    int j,k;
    for(i = 0; i<cases.filecount; i++){     //then, output all the directories
        stat(cases.filenames[i],&statStruct);
        if(S_ISDIR(statStruct.st_mode)){
            DIR* folder;
            struct dirent *ptr;
            folder = opendir(cases.filenames[i]);
            if(folder == NULL){
                printf("Unable to read directory\n");
            }
            j = 0;
            while((ptr = readdir(folder))!=NULL){   //get the names of the files inside the directory 
                if(!cases.a_case){
                    if(ptr->d_name[0] == '.'){
                        continue;
                    }
                }
                dirContentfiles[j] = ptr->d_name;   //place the files into the array
                j++;
            }
            if(cases.t_case){
                timeSorting(j, dirContentfiles,cases.filenames[i]); //sort the array
            }else{
                lexographicalSort(j, dirContentfiles);
            }
            if(j!=0 && cases.dircount+cases.notFound>1 ){
                printf("%s:\n", cases.filenames[i]);
            }
            for(k = 0; k<j;k++){
                printf("%s  ", dirContentfiles[k]);
            }
            if(i!= cases.filecount-1){
                printf("\n\n");     //to avoid extra newlines
            }
            closedir(folder);
        }
    }
    free(dirContentfiles);
    return 0;
}