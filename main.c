#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 128
#define MAX_FILENAME 16
#define NUM_BLOCKS 100


typedef struct {
    char filename[MAX_FILENAME];
    char content[BLOCK_SIZE - MAX_FILENAME];
} Block;

Block disk[NUM_BLOCKS];

void initialize_disk(){
    for (int i = 0; i < NUM_BLOCKS; i++){
        strcpy(disk[i].filename, "");
    }
}

void create_file(char *filename, char *content){
    for(int i = 0; i < NUM_BLOCKS; i++){
        if(strcmp(disk[i].filename,"")== 0){
            strncpy(disk[i].filename, filename, MAX_FILENAME);
            strncpy(disk[i].content, content, BLOCK_SIZE - MAX_FILENAME);
            return;
        }
    }
    printf('Disk is full! Cannot create file.\n');
}

void read_file(char *filename){
    for(int i = 0; i < NUM_BLOCKS; i++){
        if(strcmp(disk[i].filename, filename) == 0){
            printf("Content: %s\n", disk[i].content);
            return;
        }
    }

    printf("File not found!\n");
}

void delete_file(char *filename){
    for(int i=0; i < NUM_BLOCKS; i++){
        if(strcmp(disk[i].filename, filename) == 0){
            strcpy(disk[i].filename, "");
            return;
        }
    }
    printf("File not found!\n");
}