#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define MAX_LENGTH 1024
#define DEFAULT_FILENAME "phrases.txt"

unsigned int random_number(unsigned int range)
//  Made this because it's a convenient  way of getting a "true" random.
{
    int z;
    int x = (((intptr_t)&z) % (range&1?range:range+1));
    return (unsigned int) x;
}
unsigned int count_sentences(FILE * file)
//  Scans the file and counts newlines
{
    unsigned int retval = 0;

    while(TRUE)
    {
        char c = fgetc(file);
        if(c == EOF) break;
        else  if(c == '\n') retval++;
        else continue;
    }
    rewind(file);
    return retval;
}
void eliminate_trailing(char *  src)
//  Yeets the  trailing newline
{
    char * copy = src;
    while(*(copy++))
    {
        if(*copy== '\n')
            *copy = 0;
    }
}
void random_sentence(char * dest, FILE * file)
//   Picks a  random sentence from the file and stores it in dest
{
    unsigned int range = count_sentences(file);
    unsigned int index = random_number(range) + 1;

    while(index--) fgets(dest, MAX_LENGTH, file);
}
int main(int argc, char * argv[])
{
    FILE * file = NULL;
    if(argc > 1)
    {
         file  =fopen(argv[1], "r");
    }
    else file =  fopen(DEFAULT_FILENAME, "r");

    if(file  == NULL)
    {
        printf("Failed to open file. No fortune for you.\n");
        return 1;
    }
    char * sentence = calloc(1024, sizeof(char));

    random_sentence(sentence, file);
    eliminate_trailing(sentence);
    printf("~%s~\n", sentence);

    free(sentence);

    fclose(file);
    return 0;
}
