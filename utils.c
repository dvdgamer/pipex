/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/10/08 13:17:15 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 16:20:30 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/*
 * safe_close:
 * - Closes a file descriptor referenced by pointer `fd` if it is valid.
 * - If `fd` is NULL or *fd < 0 the function returns without calling close.
 * - After attempting close the function writes -1 into *fd to mark it
 *   as closed, preventing accidental double-closes.
 */
void	safe_close(int *fd)
{
	if (fd == NULL)
		return ;
	if (*fd < 0)
		return ;
	if (close(*fd) == -1)
		perror("safe close: error closing fd");
	*fd = -1;
}

void	free_paths(char **paths)
{
	int		i;

	i = -1;
	if (paths != NULL)
	{
		while (paths[++i] != NULL)
			free(paths[i]);
		free(paths);
	}
}
