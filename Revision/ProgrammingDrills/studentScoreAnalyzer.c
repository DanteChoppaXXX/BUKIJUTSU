// Simple Student Score Analyzer

#include <stdio.h>
#include <stdlib.h>

// Function Prototypes.
double calculate_average(double scores[], int count);
double find_max(double scores[], int count);
double find_min(double scores[], int count);
double count_above_average(double scores[], int count, double average);

int main(void){

    // Ask the user for number of students (max 50)
    int count = 0;
    printf("Enter the number of students (max 50): ");
    if(scanf("%d", &count) != 1 || count > 50) {
        fprintf(stderr, "\033[1;31m[x] Invalid Input! [ERROR]\033[0m\n");
        return EXIT_FAILURE;
    }
    
    // Store each student's score (0-100)
    double scores[count];

    printf("\n\033[1;34mEnter The Score Of Each Student (0-100):\033[0m\n");
    for (int i = 0; i < count; i++) {
        printf("Enter the score of student %d: ", i + 1);
        if(scanf("%lf", &scores[i]) != 1 || scores[i] > 100){
            fprintf(stderr, "\033[1;31m[x] Score should not be greater than 100 [ERROR]\033[0m\n");
            return EXIT_FAILURE;
        }  
    }

    // Print the student's scores.
    printf("\n\033[1;32mStudents Score:\033[0m\n");
    for (int i = 0; i < count; i++) {
        printf("Student %d scored => [\033[1;32m%.2lf\033[0m]\n", i + 1, scores[i]);
    }

    printf("\n\033[1;31mAnalysis:\033[0m\n");
    // Print the Average score.
    double average = calculate_average(scores, count);
    printf("The Average Score is\t=> [\033[1;32m%.2lf\033[0m]\n", average);

    // Print the Highest score.
    printf("The Highest Score is\t=> [\033[1;32m%.2lf\033[0m]\n", find_max(scores, count));

    // Print the Lowest score.
    printf("The Lowest Score is\t=> [\033[1;32m%.2lf\033[0m]\n", find_min(scores, count));

    // Print how many students scored above average.
    printf("Students Above Average\t=> [\033[1;33m%.0lf\033[0m]\n", count_above_average(scores, count, average));

    return EXIT_SUCCESS;
}

double calculate_average(double scores[], int count){
    double total_score = 0;

    for (int i = 0; i < count; i++) {
        total_score += scores[i];
    }
    return (total_score / (double)count);
}

double find_max(double scores[], int count){
    double highest = 0;

    for (int i = 0; i < count; i++) {
        if (highest < scores[i]) {
            highest = scores[i];
        }
    }
    return highest;
}

double find_min(double scores[], int count){
    double lowest = 100;

    for (int i = 0; i < count; i++) {
        if (lowest > scores[i]) {
            lowest = scores[i];
        }
    }
    return lowest;
}

double count_above_average(double scores[], int count, double average){
    double above_average = 0;

    for (int i = 0; i < count; i++) {
        if (scores[i] > average) {
            above_average++;
        }
    }
    return above_average;
}

