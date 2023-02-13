#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool print_found(int i) {
    printf("Pattern found at index %d\n", i);
    return true;
}

bool KMP(char pat[], char txt[]) {
    int i, j, k = 0, m = strlen(txt), n = strlen(pat), lps[n];
    memset(lps, 0, n * sizeof(int));
    // construct the LPS array
    for (i = 1; i < n; i++) {
        while (j > 0 && pat[i] != pat[j]) j = lps[j - 1];
        if (pat[i] == pat[j]) lps[i] = ++j;
    }
    i = j = k = 0;
    while (i - j <= m - n) {
        if (txt[i] == pat[j]) i++, j++;
        if (j == n) k = print_found(i - j), j = lps[j - 1];
        else if (i < m && txt[i] != pat[j]) {
            if (j) j = lps[j - 1];
            else i = i + 1;
        }
    }
    return k;
}

int main() {
    char txt[1024], pat[1024];
    printf("Please enter the text:");
    scanf("%s", txt);
    printf("Please enter the pattern:");
    scanf("%s", pat);
    if (!KMP(pat, txt)) printf("Could not find such pattern!\n");
    return 0;
}