#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int isWord;
    struct Trie* next[26];
};

struct Trie* createNode() {
    struct Trie* newNode = (struct Trie*) malloc(sizeof(struct Trie));
    newNode->isWord = 0;
    for (int i = 0; i < 26; i++)
        newNode->next[i] = NULL;
    return newNode;
}

void insert(struct Trie** ppTrie, char* word) {
    if (*ppTrie == NULL)
        *ppTrie = createNode();

    struct Trie* curr = *ppTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->next[index] == NULL)
            curr->next[index] = createNode();
        curr = curr->next[index];
    }
    curr->isWord = 1;
}

int search(struct Trie* pTrie, char* word) {
    if (pTrie == NULL)
        return 0;

    if (*word == '\0')
        return pTrie->isWord;

    int index = *word - 'a';
    return search(pTrie->next[index], word + 1);
}

int numberOfOccurrences(struct Trie* pTrie, char* word) {
    int count = 0;
    int len = strlen(word);
    struct Trie* curr = pTrie;

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (curr->next[index] == NULL)
            break;
        
        curr = curr->next[index];

        if (curr->isWord && i == len - 1)
            count++;
    }
    return count;
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++)
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);

    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie* trie = NULL;

    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}
