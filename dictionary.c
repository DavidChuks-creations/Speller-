// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 475290;

// Hash table
node *table[N];

int size_count;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hc = hash(word);
    if (table[hc] != NULL)
    {
        node *cursor = table[hc];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
             {
                return true;
             }
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // uses the ASCII equivalent to hash the first four letters of every word 
    unsigned int v =0, c = 0;

    for (int i = 0; i < 4; i++)
    {

        if (word[i] == '\0')
        {
            return v;
        }
        else if (v == 0)
        {
            c = toupper(word[i]);
            v = c - 65;

        }
        else if (toupper(word[i]) < 65 || toupper(word[i]) > 90)
        {
            c = 90;
            v = (26 * (v + 1) ) + c - 65;
        }
        else
        {
            c = toupper(word[i]);
            v = (26 * (v + 1) ) + c - 65;
        }
    }
    return v ;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file and check null
    FILE *file = fopen(dictionary, "r");
    if (file ==  NULL)
    {
        printf("unable to open file.\n");
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;

    }

    //Read strings from file one at a time
    char wordc[LENGTH + 1];
    while (fscanf(file, "%s", wordc) != EOF)
    {
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Not enough memory\n");
            return false;
        }
        strcpy(new->word, wordc);

        int hc = hash(wordc);
        if (table[hc] == NULL)
        {
            new->next = NULL;
            table[hc] = new;
            size_count++;
        }
        else
        {
            new->next = table[hc];
            table[hc] = new;
            size_count++;
        }


    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *delcursor = table[i];
        while (delcursor != NULL)
        {
            node *prevdelcursor = delcursor;
            delcursor= delcursor->next;
            free(prevdelcursor);
        }
        table[i] = NULL;
    }
    return true;

}
