/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main_loop.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 17:10:20 by dponte       #+#    #+#                  */
/*   Updated: 2025/12/02 15:18:29 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	first_child(int pipefd1[2], char *infile)
{
	int	infile_fd;

	safe_close(&pipefd1[0]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("error opening infile ");
		safe_close(&pipefd1[1]);
		return (-1);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipefd1[1], STDOUT_FILENO);
	safe_close(&pipefd1[1]);
	safe_close(&infile_fd);
	return (0);
}

static int	middle_children(int pipefd1[2], int pipefd2[2], int i)
{
	if (i % 2 != 0)
	{
		safe_close(&pipefd1[1]);
		safe_close(&pipefd2[0]);
		if (dup2(pipefd1[0], STDIN_FILENO) == -1)
			perror("dup2 error");
		if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
			perror("dup2 error");
		safe_close(&pipefd1[0]);
		safe_close(&pipefd2[1]);
	}
	if (i % 2 == 0)
	{
		safe_close(&pipefd2[1]);
		safe_close(&pipefd1[0]);
		dup2(pipefd2[0], STDIN_FILENO);
		dup2(pipefd1[1], STDOUT_FILENO);
		safe_close(&pipefd2[0]);
		safe_close(&pipefd1[1]);
	}
	return (0);
}

static int	last_child(int pipefd1[2], int pipefd2[2], char *outfile, int i)
{
	int		outfile_fd;

	safe_close(&pipefd1[1]);
	safe_close(&pipefd2[1]);
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
	{
		perror("outfile_fd:");
		return (-1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	safe_close(&pipefd1[0]);
	safe_close(&pipefd2[0]);
	safe_close(&outfile_fd);
	return (0);
}

static int	handle_children(t_pipex *pipex, int i, char **argv, char **env)
{
	if (i == 0)
	{
		printf("first child\n");
		first_child(pipex->pipefd1, argv[1]);
		execute_cmd(pipex->paths, argv[2], env);
		safe_close(&pipex->pipefd2[0]);
		safe_close(&pipex->pipefd2[1]);
		return (perror("execve"), -1);
	}
	if (i == pipex->maxchildren)
	{
		printf("last child\n");
		last_child(pipex->pipefd1, pipex->pipefd2,
			argv[pipex->maxchildren + 3], i);
		execute_cmd(pipex->paths, argv[2 + i], env);
		return (perror("execve"), -1);
	}
	else
	{
		printf("middle child\n");
		middle_children(pipex->pipefd1, pipex->pipefd2, i);
		execute_cmd(pipex->paths, argv[2 + i], env);
		return (perror("execve"), -1);
	}
	return (0);
}

int	main_loop(int argc, char **argv, char **env, char **paths)
{
	int		i;
	pid_t	pid;
	t_pipex	pipex;

	pipex.paths = paths;
	pipex.maxchildren = argc - 4;
	if (create_pipes(pipex.pipefd1, pipex.pipefd2) == -1)
		return (-1);
	i = 0;
	while (i <= pipex.maxchildren)
	{
		pid = fork();
		if (pid == -1)
			return (perror("pid"), -1);
		if (pid == 0)
		{
			if (handle_children(&pipex, i, argv, env) == -1)
				return (perror("main_loop: handle_children"), -1);
		}
		else if (pid > 0)
			back_to_parent(i, pipex.pipefd1, pipex.pipefd2);
		i++;
	}
	wait_children_close_open_pipes(i, pipex.pipefd1, pipex.pipefd2);
	return (0);
}
