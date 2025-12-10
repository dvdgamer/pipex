/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipe_functions.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/26 16:46:52 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/26 16:51:38 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipes(int pipefd1[2], int pipefd2[2])
{
	if (pipe(pipefd1) == -1)
	{
		perror("pipe creation");
		return (-1);
	}
	if (pipe(pipefd2) == -1)
	{
		safe_close(&pipefd1[0]);
		safe_close(&pipefd1[1]);
		perror("pipe creation");
		return (-1);
	}
	return (0);
}

void	back_to_parent(int i, int pipefd1[2], int pipefd2[2])
{
	if (i % 2 == 0)
		safe_close(&pipefd1[1]);
	if (i % 2 != 0)
		safe_close(&pipefd2[1]);
}

int	wait_children_close_open_pipes(t_pipex *pipex, int i)
{
	int		status;
	int		last_status;
	pid_t	child_pid;

	safe_close(&pipex->pipefd1[0]);
	safe_close(&pipex->pipefd2[0]);
	last_status = 0;
	while (i >= 0)
	{
		child_pid = waitpid(0, &status, 0);
		if (child_pid == pipex->last_pid)
			last_status = WEXITSTATUS(status);
		i--;
	}
	return (last_status);
}
