#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define MAX_TOKENS 1000

char book[] =
    "The monster screamed! The monster didn't run away. "
    "The monster ate the food! The monster danced! "
    "The monster cried! The monster laughed!";

char *tokens[MAX_TOKENS];
char *next_word[MAX_TOKENS];
int token_count = 0;

void replace_non_printable_chars_with_space() {
    for (int i = 0; book[i] != '\0'; i++) {
        if (!isprint((unsigned char)book[i])) {
            book[i] = ' ';
        }
    }
}

int find_token_id(char *word) {
    for (int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i], word) == 0)
            return i;
    }
    tokens[token_count] = word;
    token_count++;
    return token_count - 1;
}

void tokenize_and_fill() {
    char *delim = " \n\r";
    char *prev = NULL;
    char *word = strtok(book, delim);

    while (word != NULL) {
        int id = find_token_id(word);
        if (prev != NULL) {
            next_word[find_token_id(prev)] = word;
        }
        prev = word;
        word = strtok(NULL, delim);
    }
}

int token_ends_sentence(char *word) {
    char c = word[strlen(word) - 1];
    return (c == '.' || c == '?' || c == '!');
}

int main() {
    srand(time(NULL));

    replace_non_printable_chars_with_space();
    tokenize_and_fill();

    sleep(1); 

    int start;
    do {
        start = rand() % token_count;
    } while (!isupper(tokens[start][0]));

    printf("%s", tokens[start]);

    char *word = next_word[start];
    while (word != NULL) {
        printf(" %s", word);
        if (token_ends_sentence(word))
            break;
        word = next_word[find_token_id(word)];
    }

    printf("\n");
    return 0;
}
