#include <stdint.h>
#include <string.h>
#include <stdio.h>

void div_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n==0) {
        strcpy(out, "0");
        return;
    }

    while (n > 0) {
        int rem = n % base;
        n=n/base;
        if (rem < 10) {
            temp[pos++] = '0' + rem;
        }
        else {
            temp[pos++] = 'A' + (rem - 10);
        }
    }

    //Reverse the Result
    int read = pos-1;
    int write = 0;

    while (read >= 0) {
        out[write++] = temp[read--];
    }
    out[write] = '\0';

}

void sub_convert(uint32_t n, int base, char *out) {

    if (n==0) {
        strcpy(out, "0");
        return;
    }

    int power = 1;
    while (power <= n/base) {
        power *= base;
    }

    int print = 0;
    int start = 0;

    while (power > 0) {
        uint32_t num = n/power;
        if (num > 0 || start) {
            out[print++] = num + '0';
            start = 1;
        }
        n -= num * power;
        power /= base;
    }

}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    //OG number
    div_convert (n, 2, bin);
    div_convert (n, 8, oct);
    div_convert (n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    //3 Left-Shift
    uint32_t shifted = n << 3;
    div_convert (shifted, 2, bin);
    div_convert (shifted, 8, oct);
    div_convert (shifted, 16, hex);
    printf("Left Shifted by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    //AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert (masked, 2, oct);
    div_convert (masked, 8, hex);
    div_convert (masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);


}