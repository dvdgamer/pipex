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


void	create_pipe(char **argv, char **env)
{
	int		i;
	int		pipefd[2];
	char	*cmd;
	char	**paths; // will need free

	paths = extract_env(env);
	// Create pipe

	i = 2; //start at the first argument
	printf("0: %d\n", pipefd[0]);
	printf("1: %d\n", pipefd[1]);
	while (argv[i] != NULL)
	{
		printf("argv[i]: %s\n", argv[i]);
		execute_cmd(paths, argv[i], env);
		i++;
	}
}

int main (int argc, char *argv[], char *env[])
{
	int		i;
	int		maxchildren;
	int		pipefd1[2];
	int		pipefd2[2];
	char	*infile;
	char	*outfile;
	pid_t	pid;

	if (argc < 4 || empty_str_in_argv(argv)) {
		printf("No empty strings\n");
		return (0);
	}
	infile = argv[1];
	outfile = argv[argc - 1];

	if (access(outfile, F_OK) == -1)
		unlink(outfile);

	i = 0;
	// Create children
	while (i < maxchildren)
	{
		pid = fork(); // pid is the id of the child process
		/* waitpid();  // this will wait for all the child processes */
		/* accessexit(); */
		if (pid == 0 && i == 0)
		{
			pipe(pipefd1);
			//callchildfunction(i);
			// close read end
			execute_cmd();
			// error handling
			exit(0);
		}
		else if (pid == 0 && i < maxchildren - 1) // middle children
		{
			//callchildfunction(i);
			// handle pipe1 and pipe2
			// close read end
			execute_cmd();
			exit(0 + i);
		}
		else if (pid == 0 && i == maxchildren) // last child
		{
			// no pipe
			// Take write end of the pipe and output into outfile
			// exec command
			exit(100);
		}
		else if (pid == -1)
			/* error(); */
			printf("error\n");
	}

	wait(0);
	waitpid(pid, NULL, 0);

};

