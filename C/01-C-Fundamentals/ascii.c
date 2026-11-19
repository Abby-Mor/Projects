#include <stdio.h>

int main() {
    int i;
    printf("ASCII Table:\n");
    printf("Dec | Char\n");
    printf("----------\n");
    
    // 0-31 are control characters, 32-126 are printable
    for(i = 0; i <= 127; i++) {
        // Using a check to avoid printing non-printable characters 
        // in the console, e.g., for i < 32
        if(i < 32 || i == 127) {
            printf("%3d | Control/Special\n", i);
        } else {
            printf("%3d | %c\n", i, i);
        }
    }
    
    return 0;
}