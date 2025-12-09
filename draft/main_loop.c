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

static void	safe_close(int fd)
{
	if (fd >= 0)
	{
		close(fd);
		fd = -1;
	}
}

int	first_child(int pipefd1[2], char *infile)
{
	int	infile_fd;

safe_close(pipefd1[0]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd  == -1)
		return (perror("error opening infile "),safe_close(pipefd1[1]), -1);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipefd1[1], STDOUT_FILENO);
safe_close(pipefd1[1]);
safe_close(infile_fd);
	return (0);
}

int	middle_children(int pipefd1[2], int pipefd2[2], int i)
{
	if (i % 2 != 0)
	{
	safe_close(pipefd1[1]);
	safe_close(pipefd2[0]);
		if (dup2(pipefd1[0], STDIN_FILENO) == -1)
			perror("dup2 error");
		if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
			perror("dup2 error");
	safe_close(pipefd1[0]);
	safe_close(pipefd2[1]);
	}
	if (i % 2 == 0)
	{
	safe_close(pipefd2[1]);
	safe_close(pipefd1[0]);
		dup2(pipefd2[0], STDIN_FILENO);
		dup2(pipefd1[1], STDOUT_FILENO);
	safe_close(pipefd2[0]);
	safe_close(pipefd1[1]);
	}
	return (0);
}

int	last_child(int pipefd1[2], int pipefd2[2], char *outfile, int i)
{
	int		outfile_fd;

safe_close(pipefd1[1]);
safe_close(pipefd2[1]);
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
safe_close(pipefd1[0]);
safe_close(pipefd2[0]);
safe_close(outfile_fd);
	return (0);
}

void	back_to_parent(int i, int pipefd1[2], int pipefd2[2])
{
	if (i % 2 == 0)
		safe_close(pipefd1[1]);
	if (i % 2 != 0)
		safe_close(pipefd2[1]);
}

void	wait_for_children_and_close_open_pipes(int i,
				int pipefd1[2], int pipefd2[2])
{
	while (i >= 0)
	{
		wait(0);
		i--;
	}
	safe_close(pipefd1[0]);
	safe_close(pipefd2[0]);
}

static int	create_pipes(int pipefd1[2], int pipefd2[2])
{
	pipefd1[0] = -1;
	pipefd2[0] = -1;
	pipefd1[1] = -1;
	pipefd2[1] = -1;

	if (pipe(pipefd1) == -1)
	{
		perror("main: pipe creation");
		return (-1);
	}
	if (pipe(pipefd2) == -1)
	{
		safe_close(pipefd1[0]);
		safe_close(pipefd1[1]);
		perror("main: pipe creation");
		return (-1);
	}
	return (0);
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
	if (create_pipes(pipefd1, pipefd2) == -1)
		return (-1);
	while (i <= maxchildren)
	{
		pid = fork();
		if (pid == -1)
			return (perror("pid"), -1);
		if (pid == 0 && i == 0)
		{
			first_child(pipefd1, argv[1]);
			execute_cmd(paths, argv[2], env);
			safe_close(pipefd2[0]);
			safe_close(pipefd2[1]);
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
	wait_for_children_and_close_open_pipes(i, pipefd1, pipefd2);
	return (0);
}

