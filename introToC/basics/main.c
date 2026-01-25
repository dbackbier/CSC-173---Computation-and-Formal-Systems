#include <stdio.h>

int main(void) {
    float fahrenheit = 212;
    float kelvin = 5.0/9.0 * (fahrenheit - 32.0) + 273.15;
    printf("%f degrees Fahrenheit is %f Kelvins\n", fahrenheit, kelvin);
    if (fahrenheit <= 32.0) {
        printf("That's freezing!\n");
    } else if (fahrenheit >= 212.0) {
        printf("That's boiling!\n");
    } else {
        printf("That's nice!\n");
    }
    for (int i = 1; i <= 10; i++) {
        printf("%i ", i);
    }
    printf("\n");
    for (int i = 10; i >= 1; i--) {
        if (i % 2 == 0) {
            printf("%i ", i);
        }
    }

    int n;
    printf("\nEnter a number: ");
    scanf("%i", &n);
    printf("%i\n", n);

    float f;
    printf("Enter a float: ");
    scanf("%f", &f);
    printf("%f\n", f);

    char s[256];
    printf("Enter a string (no more than 255 characters): ");
    scanf("%255s", s);
    printf("%s\n", s);

    printf("Enter lines of text, enter a blank line to finish:\n");
    do {
        fgets(s, 256, stdin);
        printf("%s", s);
    } while (s[0] == '\n');
}

void printStars(int i) {
    for (int j = 0; j < i; j++) {
        printf("* ");
    }
}

float fToKelvin(float f) {
    return 5.0/9.0 * (f - 32.0) + 273.15;
}

int copy(char* file1, char* file2) {
    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "w");
    if (f1 == NULL || f2 == NULL) {
        return 0;
    }
    while (!feof(f1)) {
        char s[256];
        if (fgets(s, 255, f1) != NULL) {
            fprintf(f2, "%s", s);
        }
    }
    fclose(f1);
    fclose(f2);
    return 1;
}