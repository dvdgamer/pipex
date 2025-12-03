/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   command_execution.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 16:21:51 by dponte       #+#    #+#                  */
/*   Updated: 2025/12/02 15:16:49 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int only_white_space(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	try_exec_paths(char **paths, char *command,
				char **cmd_and_flags, char **env)
{
	int		i;
	char	*path_to_exec;

	i = 0;
	while (paths[i] != NULL)
	{
		path_to_exec = ft_strjoin(paths[i], command);
		if (path_to_exec == NULL)
		{
			perror("execute_cmd: path allocation failed");
			return (-1);
		}
		if (access(path_to_exec, F_OK) == 0)
			execve(path_to_exec, cmd_and_flags, env);
		free (path_to_exec);
		i++;
	}
	return (-1);
}

int	execute_cmd(char *paths[], char *arg_cmd, char *env[])
{
	char	*command;
	char	**cmd_and_flags;

	if (paths == NULL)
		return (perror("execute_cmd: paths is NULL"), -1);
	// TODO: empty string: ignore and still go trough with the other instructions
	if (only_white_space(arg_cmd))
		return (1);
	cmd_and_flags = ft_split(arg_cmd, ' ');
	if (cmd_and_flags == NULL || cmd_and_flags[0] == NULL)
	{
		perror("execute_cmd: ft_split failed");
		return (-1);
	}
	command = ft_strjoin("/", cmd_and_flags[0]);
	if (command == NULL)
	{
		free_paths(cmd_and_flags);
		perror("execute_cmd: strjoin failed");
		return (-1);
	}
	if (try_exec_paths(paths, command, cmd_and_flags, env) == -1)
		perror("execute_cmd: command not found or all execve attempts failed");
	free(command);
	free_paths(cmd_and_flags);
	return (-1);
}
