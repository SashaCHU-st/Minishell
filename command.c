#include "builtins.h"
void ft_pwd(char **envp)
{
	char wd[1000];
	printf("%s",getcwd(wd, sizeof(wd)));
}
void ft_cd(t_built *data,int argc, char **argv)
{
	if(argc <3)// in case after echo there is no arguments
			printf("");
		else if(argc == 3)
		{
			printf("%s\n",getcwd(data->pwd, sizeof(data->pwd)));
			if (chdir(argv[2]) != 0)
            {
                printf("ERROOR");
            }
			printf("%s",getcwd(data->pwd, sizeof(data->pwd)));
		}
}

void ft_unset(t_built *data,int argc, char **argv)
{
	int k = 2;
		int count = argc;
		if(argc == 2)
			printf("");
		if(argc >= 3)
		{
			printf("ENVP\n");
			int i = 0;
			while (data->envp[i] != NULL && data->envp[i + 1] != NULL)
				printf("%s\n", data->envp[i++]);
			while (--count > 1)
				unset_var(data->envp, argv[k++]);
			printf("\n");printf("\n");printf("\n");// DELETE THIS 
			printf("UPDATED\n");
			i = 0;
			while (data->envp[i] != NULL && data->envp[i + 1] != NULL)
				printf("%s\n", data->envp[i++]);
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

void ft_export(t_built *data, int argc, char **argv)
{
	char *after_equal_sign;
		int i =  0;
		char *env = data->envp[i];
		while (env != NULL && data->envp[i + 1] != NULL)/// envp[i + 1] dont pprint last line
		{
			after_equal_sign = ft_strchr(env, '=');
			printf("declare -x ");
			printf("%.*s", (int)(after_equal_sign - env), env);/// .* shows that the length of argument will be given as argument
			printf("=\"%s\"\n", after_equal_sign + 1);
			i++;
			env = data->envp[i];
		}	
		if(argc == 3)
		{
			char *added_var = ft_strjoin(argv[2], "");
			if (added_var != NULL)
			{
				data->envp[i] = added_var;
				data->envp[i + 1] = NULL; ///for ending list
				printf("declare -x %s\n", added_var);
			}
		}
}
void ft_env(t_built *data)
{
	int i = 0;
		char *env = data->envp[i];
		while (env != NULL)
		{
			printf("%s\n", env);
			i++;
			env = data->envp[i];
		}
}