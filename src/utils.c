/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/10/08 13:17:15 by dponte       #+#    #+#                  */
/*   Updated: 2025/12/02 15:17:06 by dponte       ########   odam.nl          */
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

char	**extract_env(char *env[])
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
