# Creating own lovely bash ❤

## Main overview
#### Implement redirections:
- `<` should redirect input.
- `>` should redirect output.
- `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- `>>` should redirect output in append mode.
  
#### Implement pipes (| character). 
The output of each command in the pipeline is connected to the input of the next command via a pipe.
#### Handle environment variables
($ followed by a sequence of characters) which should expand to their values.
#### Handle $? which should expand to the exit status of the most recently execute foreground pipeline.
#### Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
#### In interactive mode:
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits the shell.
- ctrl-\ does nothing.

#### Implement the following builtins:
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options

## Minishe Program Usage
1. Clone repository
2. Move to directory
```bash
cd minishell
```
3.Run make file
```bash
make
```
4. Run th program : example
```bash
./minishell
```
5. #### Testing the program
   
*Built in env:*
```bash
env
```
*Built in echo:*
```bash
echo "hello world"
````
*Redirections, pipes, commands:*
```bash
< Makefile cat | ls | cat > test.txt
```
*Heredoc*
```bash
<< ll
```




