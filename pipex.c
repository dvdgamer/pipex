/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/09 16:03:22 by dponte       #+#    #+#                  */
/*   Updated: 2025/10/08 16:39:30 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

// < file1 cmd1 | cmd2 > file2
//
// < infile grep ac | wc -c
// 		==
// grep ac < infile | wc -c

// < is the "input redirection" symbol
// redirects the contents of infile to standard input
// This reads the file via stdin instead of dirctly opening the file

// pipe |
// directs the output (stdout) on the left of operator to stdin to the right

// > output redirection
// points the stdout into the designated file
// replaces the contents of the receiving file

// >> appends the output to the designated file
//
// << symbol is an input "redirection" symbol
//It makes the shell read from the standard input until it encounters only a specific LIMITER on the stdin.
//LIMITER is the here document or 'heredoc'
//
//cmd << LIMITER | cmd1 >> file
//
//NOTE: If in or outfiles aren't valid they don't execute the command
/* sleep 5 < test */
/* bash: test: Permission denied */
/* sleep 5 < test | sleep 3 */
/* *sleeps for 3 secs* */
/* bash: test: Permission denied */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

bool	empty_str_in_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '\0')
			return (true);
		i++;
	}
	return (false);
}

// Gets the env varabiables
//* Trims the first env_var to remove the "PATH ="
char **extract_env(char *env[])
{
	int	i;
	int	j;
	char *env_var;
	char **env_paths;

	i = 0;
	while (env[i] != NULL)
	{
		env_var = ft_substr(env[i], 0, 4);
		// replace this function
		if (strcmp(env_var, "PATH") == 0)
		{
			env_paths = ft_split(env[i], ':');
			env_paths[0] = ft_substr(env_paths[0], 5, ft_strlen(env_paths[0]));
			free(env_var);
			return (env_paths);
		}
		free(env_var);
		i++;
	}
	return NULL;
}

int main (int argc, char *argv[], char *env[])
{
	char *infile;
	char *outfile;
	char **paths = extract_env(env); // will need free
	pid_t pid = fork(); // pid is the id of the child process

	if (argc < 4 || empty_str_in_argv(argv)) {
		printf("No empty strings\n");
		return (0);
	}
	infile = argv[1];
	outfile = argv[argc - 1];

	if (access(outfile, F_OK) == -1)
		unlink(outfile);

	if (pid == 0)
	{
		//callchildfunction(i);
		//Start all the forking and piping
		create_pipe(argv, paths, env);
		printf("hello from child process %d\n", pid);
		exit(0);
	}
	else if (pid == -1)
		/* error(); */
		printf("error\n");
	else
	{
		/* parentfunc(pid); */
		/* wait(); */
		waitpid(pid, NULL, 0);
		printf("hello from parent process %d\n", pid);
		/* waitpid();  // this will wait for all the child processes */
		/* accessexit(); */
	}
	return (0);
};

