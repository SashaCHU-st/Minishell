#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *minishell;
    while ((minishell = readline("OURminishell")) != NULL) {
        if (*minishell) {  // Если строка не пуста
            add_history(minishell);
        }
        printf("%s\n", minishell);
        free(minishell);
    }
    return 0;
}

