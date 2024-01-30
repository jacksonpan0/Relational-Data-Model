#include <stdio.h>
#include <string.h>
#include "hashtables.h"
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getInput(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character
}

void getIntegerInput(const char *prompt, int *value) {
    printf("%s", prompt);
    while (scanf("%d", value) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        clearInputBuffer();
        printf("%s", prompt);
    }
    clearInputBuffer();  // Consume the newline character
}
void repl(void) {
    while (1) {
        printf("\nChoose operation:\n");
        printf("1. Find students' grade in course using name\n");
        printf("2. Find student location during a specific time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();  // Consume the newline character
        switch (choice) {
            case 1: {
                char studentName[50];
                char courseName[50];
                getInput("Enter the student name: ", studentName, 50);
                getInput("Enter the course name: ", courseName, 50);
                findGradeForStudentInCourse(studentName, courseName);
                break;
            }
            case 2: {
                char studentName[50];
                int hour;
                char day[10];
                getInput("Enter the student name: ", studentName, 50);
                getIntegerInput("Enter the hour (as integer, e.g., 1400): ", &hour);
                getInput("Enter the day (e.g., M, T, W, R, F): ", day, 10);
                findStudentLocation(studentName, hour, day);
                break;
            }
            case 3:
                return;  // Exit the function
            default:
                printf("Not a valid option. Please try again!\n");
        }
    }
}

