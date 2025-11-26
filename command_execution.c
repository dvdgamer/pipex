/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   command_execution.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 16:21:51 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 16:21:51 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Find the PATH entry in the environment and split it into an array of
// directories. Returns NULL if PATH is not found.
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

int	execute_cmd(char *paths[], char *arg_cmd, char **env)
{
	int		i;
	int		ret;
	char	*command;
	char	*path_to_exec;
	char	**cmd_and_flags;

	i = 0;
	if (paths == NULL)
		perror("no paths");
	cmd_and_flags = ft_split(arg_cmd, ' ');
	command = ft_strjoin("/", cmd_and_flags[0]);
	while (paths[i] != NULL)
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
