#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 129
#define MAX_FILENAME 16
#define NUM_BLOCKS 3000


typedef struct {
    char filename[MAX_FILENAME];
    char content[BLOCK_SIZE];
    int next_block;
} Block;

Block disk[NUM_BLOCKS];

void initialize_disk(){
    for (int i = 0; i < NUM_BLOCKS; i++){
        strcpy(disk[i].filename, "");
        disk[i].next_block = -1;
    }
}

void create_file(char *filename, char *content){
    int i, prev = -1, first= -1;
    for(i = 0; i < NUM_BLOCKS; i++){
        if(strcmp(disk[i].filename,"")== 0){
            strncpy(disk[i].filename, filename, MAX_FILENAME);
            disk[i].filename[MAX_FILENAME - 1] = '\0';
            strncpy(disk[i].content, content, BLOCK_SIZE);
            disk[i].content[BLOCK_SIZE - 1];


            if(prev != -1){
                disk[prev].next_block = i;
            }else{
                first = i;
            }


            prev = i;
            content += BLOCK_SIZE;
                if(*content == '\0'){
                    return first;
                };
        }

    }
    printf('Disk is full! Cannot create file.\n');
    return -1;
}

int read_file(char *filename, char* buffer, int size){
    int i;
    for(i = 0; i < NUM_BLOCKS; i++){
        //find the first block of the file
        if(strcmp(disk[i].filename, filename) == 0){
            //copy the found file into the buffer with the required size
            strncopy(buffer, disk[i].content, size);
            //get the min size between the data and size 
            int bytes_read = min(strlen(disk[i].content),size);
            //subtract the  bytes read from the size
            size -= bytes_read;
            //move the buffer to the away from the file that was read
            buffer += bytes_read;
            //follow the next step links to read the rest of the file 
            int next = disk[i].next_block;

            while(next != -1 && size > 0){
            strncopy(buffer, disk[next].content, size);
            //get the min size between the data and size 
            int bytes_read = min(strlen(disk[next].content),size);
            //subtract the  bytes read from the size
            size -= bytes_read;
            //move the buffer to the away from the file that was read
            buffer += bytes_read;
            //follow the next step links to read the rest of the file 
            int next = disk[next].next_block;  
            }
        }
    }
    // for(int i = 0; i < NUM_BLOCKS; i++){
    //     if(strcmp(disk[i].filename, filename) == 0){
    //         printf("Content: %s\n", disk[i].content);
    //         return;
    //     }
    // }

    printf("File not found!\n");
    return buffer - size; //total number of bytes read 
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