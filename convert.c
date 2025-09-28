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
void oct_to_bin(const char *oct, char *out) {
    int outIndex = 0;

    for (const char *c = oct; *c != '\0'; c++) {
        char b = *c;
        if (b >= '0' && b <= '7') {
            int num = b - '0';

            for (int i = 2; i >= 0; i--) {
                int bit = (num >> i)&1;
                out[outIndex++] = bit + '0';
            }
        }
    }
    out[outIndex] = '\0';

}

void oct_to_hex(const char *oct, char *out) {
    int outIndex = 0;
    char bin [3 * strlen(oct)+1];

    oct_to_bin(oct, bin);

    int len = strlen(bin);
    int remainder = len % 4;
    int pad = (remainder == 0) ? 0 : 4 - remainder;
    char binPad[pad+len+1];
    for (int z = 0; z < pad; z++) {
        binPad[pad+z] = bin[z];
    }
    if (remainder != 0) {
        int pad = 4 - remainder;
        len = len + pad;
    }
    for (int i = 0; i <= len - 4; i+=4) {
        int nibVar = (bin [i] - '0') * 8 + (bin[i+1] - '0') * 4 + (bin[i+2] - '0') * 2 + (bin[i+3] - '0')*1;

        if (nibVar < 10) {
            out[outIndex] = nibVar + '0';
        }
        else {
            out[outIndex] = 'A' + (nibVar - 10);
        }

        outIndex++;
    }
    out[outIndex] = '\0';

}

void hex_to_bin(const char *hex, char *out) {
    int outIndex = 0;
    for (const char *c = hex; *c != '\0'; c++) {
        int num;

        if (*c >= '0' && *c <= '9') {
            int num = *c - '0';
        }
        else if (*c >= 'a' && *c <= 'f') {
            int num = *c - 'a' + 10;
        }
        else if (*c >= 'A' && *c <= 'F') {
            int num = *c - 'A' + 10;
        }
        else {
            continue;
        }
        int dig = num;

        for (int i = 3; i >= 0; i--) {
            int bit = (dig >> i) & 1;
            {
                out[outIndex] = bit + '0';
                outIndex++;
            }
        }
    }
    out[outIndex] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        out[0] = '0';
        uint32_t p = (uint32_t) n;

        for (int b = 30; b >= 0; b--) {
            int bit = (p >> b) & 1;
            out[31-b] = bit + '0';
        }

    }
    else {
        out[0] = '1';

        int64_t p = (int64_t) n;
        uint32_t p32 = (uint32_t) -p;
        for (int b = 30; b >= 0; b--) {
            int bit = (p32 >> b) & 1;
            out[31-b] = bit + '0';
        }
    }
    out[31] = '\0';
}

void to_ones_complement(int32_t n, char *out) {
    uint32_t p;
    if (n >= 0) {
        p = (uint32_t) n;
    }
    else {
        int64_t z = (int64_t)n;
        uint32_t z32 = (uint32_t)-z;
        p = ~z32;
    }

    for (int i = 31; i >= 0; i--) {
        int bit = (p >> i) & 1;
        out[31-i] = bit + '0';
    }
    out[31] = '\0';
}

void to_twos_complement(int32_t n, char *out) {
    uint32_t p = (uint32_t) n;
    for (int i = 31; i >= 0; i--) {
        int bit = (p >> i) & 1;
        out[31-i] = bit + '0';
    }
    out[31] = '\0';
}
