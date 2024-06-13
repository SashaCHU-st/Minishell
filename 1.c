#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    // Determine the number of environment variables
    int num_env_vars = 0;
    while (envp[num_env_vars] != NULL) {
        num_env_vars++;
    }

    // Allocate memory for the new environment array (with space for additional element)
    char **new_envp = (char **)malloc((num_env_vars + 2) * sizeof(char *));
    if (new_envp == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit with error
    }

    // Copy the existing environment variables to the new array
    for (int i = 0; i < num_env_vars; i++) {
        new_envp[i] = strdup(envp[i]); // strdup duplicates the string
        if (new_envp[i] == NULL) {
            printf("Memory allocation failed\n");
            // Free memory for already copied variables
            for (int j = 0; j < i; j++) {
                free(new_envp[j]);
            }
            free(new_envp);
            return 1; // Exit with error
        }
    }

    // Add a new environment variable
    char *new_env_var = argv[1];
    new_envp[num_env_vars] = strdup(new_env_var);
    new_envp[num_env_vars + 1] = NULL; // Null-terminate the array

    // Update the environment using putenv or setenv
    // putenv(new_envp[num_env_vars]); // For putenv
    // setenv("MY_NEW_ENV_VARIABLE", "NewValue", 1); // For setenv

    // Print out the modified environment
    printf("Modified environment:\n");
    for (int i = 0; new_envp[i] != NULL; i++) {
        printf("%s\n", new_envp[i]);
    }

    // Free memory for the new environment array
    for (int i = 0; i < num_env_vars + 1; i++) {
        free(new_envp[i]);
    }
    free(new_envp);

    return 0; // Exit successfully
}
