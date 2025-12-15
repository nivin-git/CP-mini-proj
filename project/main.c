#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORDS 10000
#define WORD_LEN 50

void toLower(char *str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

int extractWords(char words[][WORD_LEN], const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("Error opening %s\n", filename);
        return 0;
    }
    
    char word[WORD_LEN];
    int count = 0;

    while(fscanf(fp, "%s", word) != EOF && count < MAX_WORDS) {
        toLower(word);
        strcpy(words[count++], word);
    }

    fclose(fp);
    return count;
}

int countMatches(char file1[][WORD_LEN], int count1, char file2[][WORD_LEN], int count2) {
    int matches = 0;

    for(int i = 0; i < count1; i++) {
        for(int j = 0; j < count2; j++) {
            if(strcmp(file1[i], file2[j]) == 0) {
                matches++;
                break;
            }
        }
    }
    return matches;
}

int main() {
    char file1Words[MAX_WORDS][WORD_LEN];
    char file2Words[MAX_WORDS][WORD_LEN];

    int count1 = extractWords(file1Words, "file1.txt");
    int count2 = extractWords(file2Words, "file2.txt");

    int matched = countMatches(file1Words, count1, file2Words, count2);

    float similarity = (matched / (float)count1) * 100;

    printf("\nMatched Words: %d\n", matched);
    printf("Similarity: %.2f%%\n", similarity);

    return 0;
}
