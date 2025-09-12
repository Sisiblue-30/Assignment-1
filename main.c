#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char line[256];
    while (fgets(line, 256, file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        for (char *p =line; *p; p++) {
            char c = *p;

            if(c >= '0' && c <= '9') {
                uint32_t number = c - '0';
            } else if(c >= 'A' && c <= 'F') {
                uint32_t number = c - 'A' + 10;
            } else if(c >= 'a' && c <= 'f') {
                uint32_t number = c - 'a' + 10;
            } else {
                printf("Invalid character: %c\n", c);
            }

        }
    }
    fclose(file);
}
