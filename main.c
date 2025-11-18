#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_COUNT 15000
#define MAX_SUCCESSOR_COUNT (MAX_WORD_COUNT / 2)

char* load_book(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Could not open %s\n", filename);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

char *book; 
char *tokens[MAX_WORD_COUNT];
size_t tokens_size = 0;

char *succs[MAX_WORD_COUNT][MAX_SUCCESSOR_COUNT];
size_t succs_sizes[MAX_WORD_COUNT];

void replace_non_printable_chars_with_space() {
    for (size_t i = 0; book[i] != '\0'; i++) {
        if (!isprint((unsigned char)book[i])) {
            book[i] = ' ';
        }
    }
}

size_t token_id(char *token) {
    for (size_t id = 0; id < tokens_size; ++id) {
        if (strcmp(tokens[id], token) == 0) {
            return id;
        }
    }
    tokens[tokens_size] = token;
    return tokens_size++;
}

void append_to_succs(char *token, char *succ) {
    size_t id = token_id(token);
    size_t *next_empty_index_ptr = &succs_sizes[id];

    if (*next_empty_index_ptr >= MAX_SUCCESSOR_COUNT) {
        printf("Successor array full.\n");
        exit(EXIT_FAILURE);
    }

    succs[id][(*next_empty_index_ptr)++] = succ;
}

void tokenize_and_fill_succs(char *delimiters, char *str) {
    char *prev = NULL;
    char *tok = strtok(str, delimiters);

    while (tok != NULL) {
        token_id(tok);
        if (prev != NULL) {
            append_to_succs(prev, tok);
        }
        prev = tok;
        tok = strtok(NULL, delimiters);
    }
}

char last_char(char *str) {
    size_t len = strlen(str);
    if (len == 0) return '\0';
    return str[len - 1];
}

bool token_ends_a_sentence(char *token) {
    char c = last_char(token);
    return (c == '.' || c == '!' || c == '?');
}

size_t random_token_id_that_starts_a_sentence() {
    size_t candidates[MAX_WORD_COUNT];
    size_t count = 0;

    for (size_t i = 0; i < tokens_size; i++) {
        if (isupper((unsigned char)tokens[i][0])) {
            candidates[count++] = i;
        }
    }

    if (count == 0) return 0;
    return candidates[rand() % count];
}

char *generate_sentence(char *sentence, size_t sentence_size) {
    size_t current_token_id = random_token_id_that_starts_a_sentence();
    char *token = tokens[current_token_id];

    sentence[0] = '\0';
    strcat(sentence, token);
    if (token_ends_a_sentence(token)) return sentence;

    size_t sentence_len_next;

    do {
        size_t succ_count = succs_sizes[current_token_id];
        if (succ_count == 0) break;

        size_t next = rand() % succ_count;
        char *next_tok = succs[current_token_id][next];

        sentence_len_next = strlen(sentence) + 1 + strlen(next_tok);
        if (sentence_len_next >= sentence_size - 1) break;

        strcat(sentence, " ");
        strcat(sentence, next_tok);

        if (token_ends_a_sentence(next_tok)) break;

        current_token_id = token_id(next_tok);
    } while (1);

    return sentence;
}

int main() {
    printf("Program started.\n");

    book = load_book("../pg84.txt"); 
    printf("Loaded %zu characters.\n", strlen(book));

    replace_non_printable_chars_with_space();

    char *delimiters = " \n\r";
    tokenize_and_fill_succs(delimiters, book);

    char sentence[1000];
    srand((unsigned int)time(NULL));

    do {
        generate_sentence(sentence, sizeof(sentence));
    } while (last_char(sentence) != '?');
    puts(sentence);
    puts("");

    do {
        generate_sentence(sentence, sizeof(sentence));
    } while (last_char(sentence) != '!');
    puts(sentence);

    free(book); 
}
