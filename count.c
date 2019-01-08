// Will Schnicke
// CSE 5462 - Ogle
// Lab 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

// count will take an input binary file and a search string, as well as an
// output file. The size of the input file and the number of occurrences of the
// search string will be printed to the output file

int count_hits(char *buffer, int buf_len, char *query, int q_len);

int main(int argc, char **argv) {
    // escape clauses to check for arguments
    if (argc != 4) {
        printf("Expected 3 command line arguments, received %d\n", argc - 1);
        printf("Exiting...\n");
        exit(1);
    }
    // check if input file exists
    FILE *infile;
    if ( (infile = fopen(argv[1], "r")) == NULL) {
        printf("Failed to open input file '%s'.\n", argv[1]);
        printf("Exiting...\n");
        exit(1);
    }
    // check if output file opens
    FILE *outfile;
    if( (outfile = fopen(argv[3], "w")) == NULL) {
        printf("Failed to open output file '%s'.\n", argv[3]);
        printf("Exiting...\n");
        exit(1); 
    }
    // find length of search string
    int q_len = strlen(argv[2]);
    // tracks length of file
    int file_len = 0;
    // tracks number of matches
    int hits = 0;
    // buffer stores current BUF_SIZE characters
    char *buffer;

    while(!feof(infile)) {
        buffer = malloc(BUF_SIZE);
        // read in next chunk to buffer
        int chunk_len = fread(buffer, sizeof(char), BUF_SIZE, infile);
        file_len += chunk_len;
        hits += count_hits(buffer, chunk_len, argv[2], q_len);

        // rewind file by q_len - 1 if not at end
        // this allows to capture queries across the chunks
        if(!feof(infile)) {
            fseek(infile, 1 - q_len, SEEK_CUR);
            // subtract off difference to avoid double counting
            file_len += 1 - q_len;
        }
    }
    free(buffer);
    // print to terminal
    printf("Size of file is %d\n", file_len);
    printf("Number of matches = %d\n\n", hits);
    // print to file
    fprintf(outfile, "Size of file is %d\n", file_len);
    fprintf(outfile, "Number of matches = %d\n\n", hits);

    fclose(infile);
    fclose(outfile);
}

// returns the number of hits of query within buffer
int count_hits(char *buffer, int buf_len, char *query, int q_len) {
    int i = 0;
    int count = 0;
    while(i <= buf_len - q_len) {
        char *substr = malloc(q_len * sizeof(char));
        strncpy(substr, buffer + i, q_len);
        if(!strcmp(substr, query))
            count++;

        i++;
    }

    return count;
}
