/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main_loop.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 17:10:20 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 18:33:53 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	first_child(int pipefd1[2], char *infile)
{
	int	infile_fd;

	close(pipefd1[0]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd  == -1)
		return (perror("error opening infile "), close(pipefd1[1]), -1);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipefd1[1], STDOUT_FILENO);
	close(pipefd1[1]);
	close(infile_fd);
	return (0);
}

int	middle_children(int pipefd1[2], int pipefd2[2], int i)
{
	if (i % 2 != 0)
	{
		close(pipefd1[1]);
		close(pipefd2[0]);
		if (dup2(pipefd1[0], STDIN_FILENO) == -1)
			perror("dup2 error");
		if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
			perror("dup2 error");
		close(pipefd1[0]);
		close(pipefd2[1]);
	}
	if (i % 2 == 0)
	{
		close(pipefd2[1]);
		close(pipefd1[0]);
		dup2(pipefd2[0], STDIN_FILENO);
		dup2(pipefd1[1], STDOUT_FILENO);
		close(pipefd2[0]);
		close(pipefd1[1]);
	}
	return (0);
}

int	last_child(int pipefd1[2], int pipefd2[2], char *outfile, int i)
{
	int		outfile_fd;

	close(pipefd1[1]);
	close(pipefd2[1]);
	if (i % 2 == 0)
	{
		if (dup2(pipefd2[0], STDIN_FILENO) == -1)
			perror("dup2 error");
	}
	else
	{
		if (dup2(pipefd1[0], STDIN_FILENO) == -1)
			perror("dup2 error");
	}
	outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (outfile_fd == -1)
		return (perror("outfile_fd:"), -1);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipefd1[0]);
	close(pipefd2[0]);
	close(outfile_fd);
	return (0);
}

void	back_to_parent(int i, int pipefd1[2], int pipefd2[2])
{
	if (i % 2 == 0)
		close(pipefd1[1]);
	if (i % 2 != 0)
		close(pipefd2[1]);
}

void	wait_children_close_open_pipes(int i, int pipefd1[2], int pipefd2[2])
{
	while (i >= 0)
	{
		wait(0);
		i--;
	}
	if (pipefd1[0] != -1)
		close(pipefd1[0]);
	if (pipefd2[0] != -1)
		close(pipefd2[0]);
}

int	main_loop(int argc, char *argv[], char *env[], char *paths[])
{
	int		i;
	int		maxchildren;
	int		pipefd1[2];
	int		pipefd2[2];
	pid_t	pid;

	i = 0;
	maxchildren = argc - 4;
	if ((pipe(pipefd1) == -1) || (pipe(pipefd2) == -1))
		return (perror("pipe creation"), -1);
	while (i <= maxchildren)
	{
		pid = fork();
		if (pid == -1)
			return (perror("pid"), -1);
		if (pid == 0 && i == 0)
		{
			first_child(pipefd1, argv[1]);
			execute_cmd(paths, argv[2], env);
			close(pipefd2[0]);
			close(pipefd2[1]);
			return (perror("execve"), -1);
		}
		if (pid == 0 && i == maxchildren)
		{
			last_child(pipefd1, pipefd2, argv[argc - 1], i);
			execute_cmd(paths, argv[2 + i], env);
			return (perror("execve"), -1);
		}
		else if (pid == 0)
		{
			middle_children(pipefd1, pipefd2, i);
			execute_cmd(paths, argv[2 + i], env);
			return (perror("execve"), -1);
		}
		else if (pid > 0)
			back_to_parent(i, pipefd1, pipefd2);
		i++;
	}
	wait_children_close_open_pipes(i, pipefd1, pipefd2);
	return (0);
}
