#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    char input[100];
    char expected[100];
} TestCase;

int main(void) {
    void oct_to_bin(const char *oct, char *out);
    void oct_to_hex(const char *oct, char *out);
    void hex_to_bin(const char *hex, char *out);
    void to_sign_magnitude(int32_t n, char *out);
    void to_ones_complement(int32_t n, char *out);
    void to_twos_complement(int32_t n, char *out);


    FILE *file = fopen("C:\\Users\\sdrei\\CLionProjects\\untitled\\test.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }

    char line[100];
    char actual[100];
    TestCase test;
    int t = 0;
    int pass = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *p = line;
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0' || *p == '#') {
            continue;
        }

        int n = sscanf(p, "%49s %99s %99s", test.name, test.input, test.expected);
        if (n != 3) {
            printf("Wrong input\n");
            continue;
        }

        if (strcmp(test.name, "oct_to_bin") == 0) {
            oct_to_bin(test.input, actual);
        }
        else if (strcmp(test.name, "bin_to_oct") == 0) {
            oct_to_hex(test.input, actual);
        }
        else if (strcmp(test.name, "bin_to_hex") == 0) {
            hex_to_bin(test.input, actual);
        }
        else if (strcmp(test.name, "to_sign_magnitude") == 0) {
            int32_t n = (int32_t) strtol(test.input, NULL, 10);
        }
        else if (strcmp(test.name, "to_ones_complement") == 0) {
            int32_t n = (int32_t) strtol(test.input, NULL, 10);
            to_ones_complement;
        }
        else if (strcmp(test.name, "to_twos_complement") == 0) {
            int32_t n = (int32_t) strtol(test.input, NULL, 10);
        }
        else {
            continue;
        }
        t++;
        if (strcmp(actual, test.expected)==0) {
            printf("pass", test.name, test.input, test.expected);
            pass++;
        }
        else {
            printf("fail", test.name, test.input, test.expected);
        }
    }
    fclose(file);
}
