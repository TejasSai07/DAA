#include <stdio.h>
#include <stdlib.h>

int min_cost = 1500540; // Initialize to a large value

int assignment(int jobs, int person, int **arr, int cost, int *job) {
    // Base case: all people assigned to jobs
    if (person == jobs) {
        for (int i = 0; i < jobs; ++i) {
            if (job[i] == 0) {
                cost += arr[person - 1][i];
                min_cost = (min_cost <= cost) ? min_cost : cost;
                return min_cost;
            }
        }
    } else {
        for (int i = 0; i < jobs; ++i) {
            if (job[i] == 0) {
                job[i] = 1;
                cost += arr[person - 1][i];
                assignment(jobs, person + 1, arr, cost, job);
                cost -= arr[person - 1][i];
                job[i] = 0;
            }
        }
    }
    return min_cost;
}

int main() {
    printf("Enter the number of people/jobs:\n");
    int p;
    scanf("%d", &p);

    // Allocate memory for the 2D array
    int **arr = (int **)malloc(sizeof(int *) * p);
    for (int i = 0; i < p; ++i) {
        arr[i] = (int *)malloc(sizeof(int) * p);
    }

    // Allocate memory for the job assignment array
    int *job = (int *)calloc(sizeof(int), p);

    printf("Enter weights for each person and job:\n");
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("Minimum cost = %d\n", assignment(p, 1, arr, 0, job));

    // Free allocated memory
    for (int i = 0; i < p; ++i) {
        free(arr[i]);
    }
    free(arr);
    free(job);

    return 0;
}
