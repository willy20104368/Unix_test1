    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1024

int myCompare(const void* a, const void* b) 
{ 
 
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 
int main(int argc, char *argv[]) {
    FILE *file, sorted_file;
    char line[MAX_SIZE];
    char prev_line[MAX_SIZE];
    int count = 1;
    int case_insensitive = 0;
    int unique = 0;
    int count_lines = 0;
    int run = 0;

    // Checking flags
    // todo : any order, (-icu or -i -c -u)沒說可不做
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            case_insensitive = 1;
        }
        if (strcmp(argv[i], "-u") == 0) {
            unique = 1;
        }
        if (strcmp(argv[i], "-c") == 0) {
            count_lines = 1;
        }
        else // to do
        {
            //read file path
        }
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-i] [-u] [-c] <filename>\n", argv[0]);
        exit(1);
    }

    file = fopen(argv[argc - 1], "r");
    if (file == NULL) {
        perror("Error");
        exit(1);
    }
    //read lines
    while(fgets(line, MAX_SIZE, file) != NULL) {
        run++;
    }
    //set file position to first
    fseek(file, 0, SEEK_SET);
    char** str = (char**)malloc(run* sizeof(char*));
    for(int i = 0;i<run;i++){
        str[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    }
    int copy_run = 0;
    //copy file to array of string and sort
    while(fgets(line, MAX_SIZE, file) != NULL) {
        strcpy(str[copy_run++], line);
    }
    qsort(str, run, sizeof(const char*), myCompare);


    //fgets(prev_line, MAX_SIZE, file);
    int loop = 0;
    while (loop++ <run) {
        strcpy(line, str[loop]);
        if (case_insensitive) {
            if (strcasecmp(line, prev_line) != 0) {
                if (!unique || (unique && count == 1)) {
                    if (count_lines) {
                        printf("%d ", count);
                    }
                    printf("%s", prev_line);
                }
                strcpy(prev_line, line);
                count = 1;
            } else {
                count++;
            }
        } else {
            if (strcmp(line, prev_line) != 0) {
                if (!unique || (unique && count == 1)) {
                    if (count_lines) {
                        printf("%d ", count);
                    }
                    printf("%s", prev_line);
                }
                strcpy(prev_line, line);
                count = 1;
            } else {
                count++;
            }
        }
        
    }

    // Print the last line if needed
    if (!unique || (unique && count == 1)) {
        if (count_lines) {
            printf("%d ", count);
        }
        printf("%s", prev_line);
    }

    fclose(file);
    return 0;
}   