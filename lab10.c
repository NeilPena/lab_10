#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26

// Trie structure
struct Trie
{	
    int count; 
    struct Trie *children[ALPHABET_SIZE]; 
};

//Function to initialze the node and set all to null
struct Trie *initializeNode(){

    //Allocate the memory
    struct Trie *node = (struct Trie*)malloc(sizeof(struct Trie));

    //If there is a node then allocate it all to null
     if(node){
        node -> count = 0; 
        for(int i = 0; i < ALPHABET_SIZE; i++){
            node -> children[i] = NULL; 
        }
     }
     return node; 
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    //Create a trie
    struct Trie* curr = pTrie;

    //Get the words length and loop through the entire word
    int len = strlen(word); 
    for(int i = 0; i < len; i++){
        int index = word[i] - 'a'; 
        
        //If index is out of bounds return
        if (index < 0 || index >= ALPHABET_SIZE) {
            return;
        }
        
        //If the letter is not there create a new node with the letter
        if (!curr -> children[index]){
            curr -> children[index] = initializeNode(); 
            if (!curr -> children[index]) {
                return;
            }
        }
        //Traverse through the trie
        curr = curr -> children[index]; 
    }
    //Increment the count
    curr -> count++; 
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //Create a trie struct and name it current
    struct Trie *curr = pTrie;
    //Get the length of the word and loop it 
    int len = strlen(word);
    for(int i =0; i < len; i++){
        int index = word[i] - 'a';

        //If the letter comes out null at the index then return  
        if(!curr -> children[index]){
            return 0; 
        }
        //If not traverse
        curr = curr -> children[index];
    }

    //Return the tries count
    return curr -> count++; 
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    //If trie is null return null
    if(!pTrie){
        return NULL; 
    }
    //If not null then go through every node and recurse
    for(int i; i < ALPHABET_SIZE; i++){
        if(pTrie -> children[i]){
            deallocateTrie(pTrie -> children[i]); 
        }
    }

    //Free trie
    free(pTrie); 
}

// Initializes a trie structure
struct Trie *createTrie()
{
    return initializeNode(); 
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    //Open the file
    FILE *fp = fopen(filename, "r");

    //If null then return 
    if (!fp){
        printf("Error opening file");
        return 0;
    }
    //Initialize count to 0 and set to 256 characters including null character 
    int count = 0;
    char word[256];

    //Reads in the word one by one up to 255 characters
    while (fscanf(fp, "%255s", word) == 1 && count < 256) {

        //Allocate the memory for the word
        pInWords[count] = (char *)malloc(strlen(word) + 1);

        //Copy the word into allocated memory
        strcpy(pInWords[count], word);
        count++;
    }
    //Close the file and return the number of words read
    fclose(fp);
    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}