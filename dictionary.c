/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
 
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "dictionary.h"
 
// prototype
int hash(const char* key);
 
// counter
int sizebook = 0;
 
// struct definition
typedef struct node
{
    char word[LENGTH +1];
    struct node* next;
}
node;
 
// Hash table definition
#define SIZE 500
node* HASHTABLE[490];
 
node* new_node = NULL;
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // stores index
    int position = hash(word);
    // cursor
    node* crawler = HASHTABLE[position];
    char dest[strlen(word) + 1];
    strcpy(dest, word);
    for (int i = 0, n = strlen(dest); i < n; i++)
    dest[i] = tolower(dest[i]);
    while (crawler != NULL)
    {
        if (strcmp(crawler -> word, dest) == 0)
        return true;
        crawler = crawler -> next; 
    }
    return false;
}
 
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* book = fopen(dictionary, "r");
    if (book == NULL)
    return false;
    while (!feof(book))
    {
        // new node
        node* new_node = malloc(sizeof(node));
        if(fscanf(book, "%s", new_node -> word) == 1)
        {
            // hashing
            int position = hash(new_node -> word);
            sizebook++;
            // insertion
            new_node -> next = NULL;
            new_node -> next = HASHTABLE[position];        
            HASHTABLE[position] = new_node;   
            new_node = NULL;
        }
        free(new_node);
     
    }
    // close dictionary
    fclose(book);    
    return true;
}
 
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return sizebook;
}
 
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < SIZE; i++)
    {
        node* cursor = HASHTABLE[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
}
 
int hash(const char* key)
{
    /*
     *Uses the length, first letter and last letter for hashing
    */
    int firstletter = tolower(key[0]) - 'a';
    int length = strlen(key);
    int lastletter = tolower(key[length-1]);
    int hashed = firstletter + (length * lastletter);
    return hashed % 490;
} 
