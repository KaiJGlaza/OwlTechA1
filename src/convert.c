#include <stdio.h>
#include <stdint.h>
#include <string.h>

void div_convert(uint32_t n, int base, char *out) {
    char temp [65]; // 64 bits
    int pos = 0;

    if (n == 0) { // Error catch if 0
        strcpy(out, "0"); 
        return;
    }

    while (n > 0) {
        int remainder = n % base; 
        n = n / base;

        if (remainder < 10)
            temp[pos++] = (char)('0' + remainder); // it kept giving errors so I wrapped
        else // Hexadecimal
            temp[pos++] = (char)('A' + (remainder - 10)); // Hexadecimal letters only start at 10
    }
    // Starting at the end (pos - 1) and working backwards
    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - i - 1];
    }

    out[pos] = '\0'; // Adds terminator at the end regardless of base
}

void sub_convert(uint32_t n, int base, char *out) {
    // printf("sub_convert called: n=%u, base=%d\n", n, base); // Commented out robustness error testing
    char temp [65];
    int pos = 0;
    if (out == NULL) return; // Empty catch
    
    if (n == 0) { // Error catch if 0
        strcpy(out, "0"); 
        return;
    }

    // Find the highest power of base that fits in n -> goes down later
    uint32_t power = 1;
    while (power <= n / base) {
        power = power * base;
    }

    // Now subtract powers and build the number
    while (power > 0) {
        int digit = 0;
        while (n >= power) {
            n = n - power;
            digit++; // Storing it almost because it resets every time idk how to explain
        }
        
        if (digit < 10)
            temp[pos++] = '0' + digit; // Thank you Prof Bradley
        else // Hexadecimal
            temp[pos++] = 'A' + (digit - 10); // Hexadecimal letters only start at 10
        
        power = power / base;
    }
    // No loop method because its already facing the right way
    temp[pos] = '\0';
    strcpy(out, temp);
}


void print_tables(uint32_t n) { 
    char bin [33] , oct [12] , hex [9];

    // Original number
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
            bin, oct, n, hex);
    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
            bin, oct, shifted, hex);
    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with OxFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
            bin, oct, masked, hex);
}