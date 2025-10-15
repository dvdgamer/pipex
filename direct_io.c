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
#include <stdio.h>

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

//TODO: Handle errors
void	execute_cmd(char **paths, char *cmd, char **env)
{
	int		i;
	char	*path_to_exec;

	i = 0;
	if (paths == NULL)
		printf("error");
	cmd = ft_strjoin("/", cmd);

	while(paths[i])
	{
		path_to_exec = ft_strjoin(paths[i], cmd);
		printf("path_to_exec: %s\n", path_to_exec);
		if (path_to_exec == NULL)
			printf("error");
		if (access(path_to_exec, F_OK) == 0)
		{
			printf("access === 0\n");
			// check return
			if (execve(path_to_exec, &cmd, env) != -1)
				perror("error execve");
			else
			{
				
			}
		}
		else
			free (path_to_exec);
		i++;
	}
}


//Need to define infile as stdin of the command
//Dup2 the result as stdin for the next function
// If it can't find a path it'll look for it in the current directory
