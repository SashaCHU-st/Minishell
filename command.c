#include "builtins.h"

void ft_cd(int argc, char **argv)
{
	char wd[1000];
	if(argc <3)// in case after echo there is no arguments
			printf("");
		else if(argc == 3)
		{
			printf("%s\n",getcwd(wd, sizeof(wd)));
			if (chdir(argv[2]) != 0)
            {
                printf("ERROOR");
            }
			printf("%s",getcwd(wd, sizeof(wd)));
		}
}

void ft_unset(int argc, char **envp, char **argv)
{
	int k = 2;
		int count = argc;
		if(argc == 2)
			printf("");
		if(argc >= 3)
		{
			printf("ENVP\n");
			int i = 0;
			while (envp[i] != NULL && envp[i + 1] != NULL)
				printf("%s\n", envp[i++]);
			while (--count > 1)
				unset_var(envp, argv[k++]);
			printf("\n");printf("\n");printf("\n");// DELETE THIS 
			printf("UPDATED\n");
			i = 0;
			while (envp[i] != NULL && envp[i + 1] != NULL)
				printf("%s\n", envp[i++]);
		}
}

void ft_echo(int argc, char **argv)
{
	int flag =0;
	int i = 2;
	if(argc > 2 && ft_strncmp(argv[2], "-n", 3) == 0)// in case there is -n as 3d arg
		{
			flag = 1;
			i = 3;
		}
		if(argc <=2)// in case after echo there is no arguments
			printf("there is nothing to print, put some arg"); 
		else
		{
			while(argc > i)
			{
				printf("%s", argv[i]);
				if(argc - 1 > i)
					printf(" ");
				i++;
			}
			if(!flag)
				printf("\n");
		}
}

void ft_export(char *env, char **envp, int argc, char **argv)
{
	char *after_equal_sign;
		int i =  0;
		env = envp[i];
		while (env != NULL && envp[i + 1] != NULL)/// envp[i + 1] dont pprint last line
		{
			after_equal_sign = ft_strchr(env, '=');
			printf("declare -x ");
			printf("%.*s", (int)(after_equal_sign - env), env);/// .* shows that the length of argument will be given as argument
			printf("=\"%s\"\n", after_equal_sign + 1);
			i++;
			env = envp[i];
		}	
		if(argc == 3)
		{
			char *added_var = ft_strjoin(argv[2], "");
			if (added_var != NULL)
			{
				envp[i] = added_var;
				envp[i + 1] = NULL; ///for ending list
				printf("declare -x %s\n", added_var);
			}
		}
}
void ft_env(char *env, char **envp)
{
	int i = 0;
		env = envp[i];
		while (env != NULL)
		{
			printf("%s\n", env);
			i++;
			env = envp[i];
		}
}