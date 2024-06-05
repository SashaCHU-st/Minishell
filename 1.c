//#include <stdio.h>

//int main(int argc, char *argv[], char *envp[]) {
//    // Determine the number of environment variables
//    int num_env_vars = 0;
//    while (envp[num_env_vars] != NULL) {
//        num_env_vars++;
//    }

//    // Create a one-dimensional array of strings
//    char *array[num_env_vars];

//    // Copy environment variables to the array
//    for (int i = 0; i < num_env_vars; i++) {
//        array[i] = envp[i];
//    }

//    // Print the array
//    for (int i = 0; i < num_env_vars; i++) {
//        printf("%s\n", array[i]);
//    }

//    return 0;
//}
#include <stdio.h>
#include <string.h>
#include "builtins.h"
size_t	ft_strlen(const char *str )
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void deleteEnvVar(char **envp, const char *arg)
{
	int i;
	int j;
	int len = ft_strlen(arg);
	i = 0;
	while (envp[i] != NULL)
	{
		
		if (ft_strncmp(envp[i], arg, len) == 0)
			break;
		i++;
	}
	if (envp[i] == NULL)
	{
		printf("Environment variable not found.\n");
		return;
	}
	j = i;
	while(envp[j] != NULL)
	{
		envp[j] = envp[j + 1];
		j++;
	}
	printf("Environment variable \"%s\" deleted successfully.\n", arg);
}

int main(int argc, char *argv[], char *envp[])
{

    printf("Original environment variables:\n");
    int i =  0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}

	int k = 1;
	int count = argc - 1;
	while (count)
	{
		deleteEnvVar(envp, argv[k]);
		k++;
		count--;
	}
	
    

    printf("Environment variables after deletion:\n");
	i =  0;
    while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
    return 0;
}
