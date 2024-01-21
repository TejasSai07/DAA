#include <stdio.h>
#include <string.h>

int bruteForceStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m)  // pattern found
            return i;
    }

    return -1;  // pattern not found
}

int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    int result = bruteForceStringMatch(text, pattern);

    if (result != -1)
        printf("Pattern found at index %d\n", result);
    else
        printf("Pattern not found\n");

    return 0;
}
