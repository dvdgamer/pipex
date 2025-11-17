/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   command_execution.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 16:21:51 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 16:22:07 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(char *paths[], char *arg_cmd, char **env)
{
	int		i;
	int		ret;
	char	*command;
	char	*path_to_exec;
	char	**cmd_and_flags;

	i = 0;
	if (paths == NULL)
		printf("error");
	cmd_and_flags = ft_split(arg_cmd, ' ')	;
	command = ft_strjoin("/", cmd_and_flags[0]);

	while(paths[i] != NULL)
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

