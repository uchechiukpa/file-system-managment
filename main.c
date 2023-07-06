#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initialize_disk();
int create_file(char *filename, char *content);
void read_file(char* filename, char* buffer, int size);


#define BLOCK_SIZE 129
#define MAX_FILENAME 20
#define NUM_BLOCKS 3000
#define min(a,b) ((a) < (b) ? (a) : (b));


typedef struct {
    char filename[MAX_FILENAME];
    char content[BLOCK_SIZE];
    int next_block;
} Block;

Block disk[NUM_BLOCKS];



int main(){


    char note[40]  = "things fall apart";
    char content[100]  = "things are never the same if they are not used the way they should but thats fine, as you were";

    // char buffer[1024];
    int size = 1000;

    initialize_disk();
    int first = create_file(note, content);
    printf("%i from create\n", first);
    char* buffer = malloc(size * sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory for buffer\n");
    return 1;
    }
    // printf("%s buffer before initialized\n", buffer);
    read_file(note, buffer, size );

    // printf("%s", buffer);
    // printf("%s from main\n", disk[0].content);
    // printf("%s from main\n", disk[0].filename);
    // printf("%i from main\n", disk[0].next_block);

    return 0;
}

void initialize_disk(){
    for (int i = 0; i < NUM_BLOCKS; i++){
        strcpy(disk[i].filename, "");
        disk[i].next_block = -1;
    }
}

int create_file(char *filename, char *content){
    int i, prev = -1, first= -1;
    for(i = 0; i < NUM_BLOCKS; i++){
        if(strcmp(disk[i].filename,"")== 0){
            strncpy(disk[i].filename, filename, MAX_FILENAME);
            disk[i].filename[MAX_FILENAME - 1] = '\0';
            strncpy(disk[i].content, content, BLOCK_SIZE);
            disk[i].content[BLOCK_SIZE - 1] = '\0';


            if(prev != -1){
                disk[prev].next_block = i;
            }else{
                first = i;
            }


            prev = i;
            content += BLOCK_SIZE;
                if(*content == '\0'){
                    printf("file created\n");
                    return first;
                };
        }

    }
    printf("Disk is full! Cannot create file.\n");
    return -1;
}

void read_file(char* filename, char* buffer, int size){
    int i;
    printf("%s\n", filename);
    printf("%s filename from disk\n", disk[0].filename);
    for(i = 0; i < NUM_BLOCKS; i++){
        //find the first block of the file
        // printf("%s here", disk[i].filename);
        if(strcmp(disk[i].filename, filename) == 0){
            //copy the found file into the buffer with the required size
            strncpy(buffer, disk[i].content, size);
            //get the min size between the data and size 
            int bytes_read = min(strlen(disk[i].content),size);
            //subtract the  bytes read from the size
            size -= bytes_read;
            //move the buffer to the away from the file that was read
            // buffer += bytes_read;
            printf("%i size\n", size);
            printf("%i bytes_read\n", bytes_read);
            printf("%s buffer", buffer);
            //follow the next step links to read the rest of the file 
            int next = disk[i].next_block;

            while(next != -1 && size > 0){
            strncpy(buffer, disk[next].content, size);
            //get the min size between the data and size 
            int bytes_read = min(strlen(disk[next].content),size);
            //subtract the  bytes read from the size
            size -= bytes_read;
            //move the buffer to the away from the file that was read
            buffer += bytes_read;
            
            //follow the next step links to read the rest of the file 
            int next = disk[next].next_block;  
            }
            return; //total number of bytes read 
        }
        
    }
    // printf("file here\n");
    printf("%s here\n", disk[0].filename);
    // return buffer;
}

// void delete_file(char *filename){
//     for(int i=0; i < NUM_BLOCKS; i++){
//         if(strcmp(disk[i].filename, filename) == 0){
//             strcpy(disk[i].filename, "");
//             return;
//         }
//     }
//     printf("File not found!\n");
// }