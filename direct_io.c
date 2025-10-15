/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   direct_io.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/10/08 15:51:01 by dponte       #+#    #+#                  */
/*   Updated: 2025/10/08 15:56:38 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
* Gets the env varabiables
* Trims the first env_var to remove the "PATH ="
*/
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

