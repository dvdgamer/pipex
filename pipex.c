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
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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

int		execute_cmd(char *paths[], char *arg_cmd, char **env)
{
	int		i;
	int		ret;
	char	*command;
	char	*path_to_exec;
	char	**cmd_and_flags;

	i = 0;
	if (paths == NULL)
		printf("error");
	cmd_and_flags = ft_split(arg_cmd, ' ')	;
	command = ft_strjoin("/", cmd_and_flags[0]);

	while(paths[i] != NULL)
	{
		path_to_exec = ft_strjoin(paths[i], command);
		if (path_to_exec == NULL)
			printf("error");
		if (access(path_to_exec, F_OK) == 0)
		{
			ret = execve(path_to_exec, cmd_and_flags, env);
			if (ret == -1)
				perror("error execve");
		}
		else
			free (path_to_exec);
		i++;
	}
	free (command);
	free (cmd_and_flags);
	return (ret);
}

int main (int argc, char *argv[], char *env[])
{
	int		i;
	int		maxchildren;
	int		infile_fd;
	int		pipefd1[2];
	int		pipefd2[2];
	ssize_t	bytes_read;
	char	*infile;
	char	*outfile;
	char	**paths; // will need free
	char	buffer[1024];
	pid_t	pid;

	paths = extract_env(env);

	if (argc < 4 || empty_str_in_argv(argv)) {
		printf("No empty strings\n");
		return (0); }
	infile = argv[1];
	outfile = argv[argc - 1];

	if (access(outfile, F_OK) == -1)
		unlink(outfile);

	i = 0;
	maxchildren = argc - 3;
	pipe(pipefd2);
	pipe(pipefd1);

	printf("maxchilldren: %d\n", maxchildren);
	while (i <= maxchildren)
	{
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "fork Failed  ");
			return (1);
		}

		if (pid == -1)
			return (printf("error"), 1); //TODO: Actual error handling
		if (access(infile, R_OK) == -1)
			printf("error smeerpijp"); // TODO: Free everyting

		if (pid == 0 && i == 0) // First child
		{
			close(pipefd1[0]);
			infile_fd = open(infile, O_RDONLY);
			printf("first child \n");
			dup2(infile_fd, STDIN_FILENO);
			dup2(pipefd1[1], STDOUT_FILENO);
			close(pipefd1[1]);
			close(infile_fd);
			execute_cmd(paths, argv[2], env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0 && i > 0 && i < maxchildren) // Middle children
		{
			// check if it's the second to last child
			// 	if so put it in the pipe that will write to last child
			close(pipefd1[1]);
			printf("middle child \n");
			dup2(pipefd1[0], STDIN_FILENO);
			close(pipefd1[0]);
			execute_cmd(paths, argv[2 + i], env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0 && i == maxchildren) // Last child
		{
			printf("last child\n");
			// Take write end of the pipe and output into outfile
			int outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY);
			// write to outfile
			/* write(outfile_fd,  ); */
			exit(100);
		}
		else if (pid == -1)
			printf("error\n");
		i++;
	}
	if (pid > 0)
	{
		wait(NULL);
		printf("back to parent\n");
		waitpid(pid, NULL, 0);
		return (0);
	}
};

