#include "builtins.h"
#include "minishell.h"
void ft_pwd()
{
	char wd[1000];
	printf("%s\n",getcwd(wd, sizeof(wd)));
}
void ft_cd(t_built *data, int number_of_inputs)
{
	if(number_of_inputs <  2)// in case after echo there is no arguments
			printf(" ");
		else if(number_of_inputs == 2)
		{
			printf("%s\n",getcwd(data->pwd, sizeof(data->pwd)));
			if (chdir(data->inputs[1]) != 0)
            {
                printf("ERROOR");
            }
			printf("%s\n",getcwd(data->pwd, sizeof(data->pwd)));
		} 
}

int is_var_in_envp(char *var, char **envp)
{
    int i = 0;
    int len = strchr(var, '=') - var;
    while (envp[i] != NULL)
    {
        if (strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
        {
            return i;
        }
        i++;
    }
    return -1;
}

void ft_export(t_built *data, int number_of_inputs)
{
    char *added_var;
    int j = 1;
    int i = 0;

    printf("Number of inputs: %d\n", number_of_inputs);

    if (number_of_inputs > 1)
    {
        while (j < number_of_inputs)
        {
            int var_index = is_var_in_envp(data->inputs[j], data->envp);
            if (var_index >= 0) // Variable exists, update it
            {
                free(data->envp[var_index]);
                added_var = strdup(data->inputs[j]);
                if (added_var != NULL)
                {
                    data->envp[var_index] = added_var;
                    printf("declare -x %s\n", added_var);
                }
            }
            else // Variable does not exist, add it
            {
                // Count the number of current environment variables
                while (data->envp[i] != NULL)
                    i++;

                // Allocate memory for the new environment array
                char **new_envp = malloc((i + 2) * sizeof(char *));
                if (new_envp == NULL)
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }

                // Copy the old environment variables to the new array
                for (int k = 0; k < i; k++)
                {
                    new_envp[k] = data->envp[k];
                }

                // Add the new variable
                added_var = strdup(data->inputs[j]);
                if (added_var != NULL)
                {
                    new_envp[i] = added_var;
                    new_envp[i + 1] = NULL;

                    // Free the old environment array if it was allocated
                    free(data->envp);
                    data->envp = new_envp;

                    printf("declare -x %s\n", added_var);
                }
                else
                {
                    free(new_envp);
                }
            }
            j++;
        }
    }
    else if (number_of_inputs == 1)
    {
        printf("ONLY EXPORT\n");
        i = 0;
        while (data->envp[i] != NULL)
        {
            char *kuku = strchr(data->envp[i], '=');
            if (kuku != NULL)
            {
                printf("declare -x %.*s=\"%s\"\n", (int)(kuku - data->envp[i]), data->envp[i], kuku + 1);
            }
            else
            {
                printf("declare -x %s\n", data->envp[i]);
            }
            i++;
        }
    }
}



void ft_unset(t_built *data, int number_of_inputs)
{
	int k = 1;
		//int count = number_of_inputs;
		if(number_of_inputs == 1)
			printf(" ");
		if(number_of_inputs >= 2)
		{
			//printf("ENVP\n");
			//int i = 0;
			//while (data->envp[i] != NULL && data->envp[i + 1] != NULL)
			//	printf("%s\n", data->envp[i++]);
			//while (--count > 1)
			//	unset_var(data, data->inputs[k]);
			while(k < number_of_inputs)
			//{
				unset_var(data, data->inputs[k++]);
			//	k++;
			//}
			printf("\n");printf("\n");printf("\n");// DELETE THIS 
			printf("UPDATED\n");
			int i = 0;
			while (data->envp[i] != NULL && data->envp[i + 1] != NULL)
				printf("%s\n", data->envp[i++]);
		}
}

void ft_echo(t_built *data, int number_of_inputs)
{
	int flag =0;
	int i = 2;
	if(number_of_inputs > 2 && ft_strncmp(data->inputs[1], "-n", 3) == 0)// in case there is -n as 3d arg
	{
			flag = 1;
			i = 3;
	}
	if(number_of_inputs <=1)// in case after echo there is no arguments
		printf("there is nothing to print, put some arg"); 
	else
	{
		while(number_of_inputs >= i)
		{
			printf("%s", data->inputs[i-1]);
			if(number_of_inputs - 1 > i)
				printf(" ");
			i++;
		}
		if(!flag)
			printf("\n");
	}
}

void ft_env(t_built *data)
{	
	int i = 0;
	//char *env = data->envp[i];
	while (data->envp[i] != NULL)
	{
		char  *kuku = ft_strchr(data->envp[i], '=');
		if(kuku != NULL)
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
		else
			i++;
		

	}
}