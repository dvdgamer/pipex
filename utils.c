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

void	ft_close(int fd)
{
	if (close(fd) == -1)
		perror("error closing\n");
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
