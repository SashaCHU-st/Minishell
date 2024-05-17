

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

// EXIT

void test_exit(void)
{

// check
// bash -c "exit 255"
// echo $?

	//	builtin_exit(data, env_list);

// status 123
	printf("Status = 123\n");
	char *test_args[] = {"123", NULL}; 
	builtin_exit(test_args);

// "bash: line 0: exit: abc: numeric argument required" 
	printf("Status = bash: line 0: exit: abc: numeric argument required\n");
	char *test_args2[] = {"abc", NULL}; 
	builtin_exit(test_args2);

// "bash: line 0: exit: too many arguments"
	printf("Status = bash: line 0: exit: too many arguments\n");
	char *test_args3[] = {"123", "456", NULL};
	builtin_exit(test_args3);

// status 1
	printf("Status = 1\n");
	char *test_args4[] = {"257", NULL}; 
	builtin_exit(test_args4); 

// status 255
	printf("Status = 255\n");
	char *test_args5[] = {"-1", NULL};
	builtin_exit(test_args5);

// status 0
	printf("Status = 0\n");
	char *test_args6[] = {"-9223372036854775808", NULL};
	builtin_exit(test_args6);

// status 0
	printf("Status = 0\n");
	char *test_args7[] = {NULL};
	builtin_exit(test_args7);

}

// PWD
void test_pwd()
{
	printf("G_ret_number = 0");
	builtin_pwd();

//check 
	char temp_dir[] = "temp_dir_for_testing";
	mkdir(temp_dir, 0777); 
	chdir(temp_dir);
	rmdir(temp_dir);
	builtin_pwd(); 

}

// ENV

void test_env(t_env *env_list)
{    
	builtin_env(env_list);
}


// UNSET

void test_unset(t_env *env_list)
{

(void) env_list;

	t_env *env_test = malloc(sizeof(t_env));
	env_test->name = ft_strdup("VAR1");
	env_test->value = ft_strdup("value1");
	env_test->next = NULL;

	char *test_arg1[] = {"VAR1", NULL}; // change

	printf("Name: %s, Value: %s\n", env_test->name, env_test->value);
	builtin_unset(test_arg1, &env_test);

	printf("After unset:\n");
	t_env *current = env_test;
	while (current != NULL) {
		printf("Name: %s, Value: %s\n", current->name, current->value);
		t_env *temp = current;
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

// EXPORT
void    test_export(t_env *env_list)
{
	(void) env_list;

	 t_env *env_test = NULL;


	char *env[] = {
		"VAR1=value1",
		"VAR2=value2",
		NULL
	};
	init_env(env, &env_test);
	// test data validation
	export_non_arg(&env_test);

// test to add an environment variable
	char *add_arg[] = {
		"VAR3=newvalue",
		NULL
	};
	builtin_export(add_arg, &env_test);
	printf("Environment after adding VAR3:\n");
	export_non_arg(&env_test);


// environment variable update tast
	char *update_arg[] = {
		"VAR1=newvalue1",
		NULL
	};
	builtin_export(update_arg, &env_test);
	printf("\nEnvironment after updating VAR2:\n");
	export_non_arg(&env_test);


// test to add an environment variable with invalid name
	char *invalid_arg[] = {
		"invalid_var=value",
		"1invalid=value",
		NULL
	};
	builtin_export(invalid_arg, &env_test);
	printf("\nEnvironment after attempting to add invalid variables:\n");
	export_non_arg(&env_test);

	// free memory
	while (env_test != NULL) {
		t_env *temp = env_test;
		env_test = env_test->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	} 
}


// CD

void test_cd()
{
// Создаем тестовый список переменных окружения
 //   t_env *env_test = NULL;

    // Создаем переменные окружения HOME и PWD
  //  add_env_argument(&env_test, "HOME=/home/user");
  //  add_env_argument(&env_test, "PWD=/home/user");
	 
	 t_env *env_test = NULL;


	char *env[] = {
		"HOME=/home/user",
		"PWD=/home/user",
		NULL
	};
	init_env(env, &env_test);


    // Without arguments
	printf("\n");
	printf("Without arguments\n");
    char *test_arg1[] = {NULL};
    builtin_cd(test_arg1, env_test);
	builtin_pwd();


    // arg = /tmp
	printf("\n");
	printf("arg = /tmp\n");
    char *test_arg2[] = {"/tmp", NULL};
    builtin_cd(test_arg2, env_test);
	builtin_pwd();

    // arg = /nonexistent
	printf("\n");
	printf("arg = /nonexistent\n");
    char *test_arg3[] = {"/nonexistent", NULL};
    builtin_cd(test_arg3, env_test);
	builtin_pwd();


    // Очищаем память
    while (env_test != NULL) {
        t_env *temp = env_test;
        env_test = env_test->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }

}

void test_builtins(t_env *env_list)
{
    (void) env_list;
 //   test_exit();
//    test_pwd();
//    test_env(env_list);

//        test_unset(env_list);

//  test_export(env_list);
 //   char *test_arg2[] = {"/tmp", NULL};
//    builtin_cd(test_arg2, env_list);
//	builtin_pwd();
//	test_cd();
//	test_pwd();

 //  test_cd();
  // test_echo();
}