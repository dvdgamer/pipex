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

#include "libft/libft.h"
#include "pipex.h"

static void	free_command_and_flags(char *command, char **cmd_and_flags)
{
	free(command);
	free_paths(cmd_and_flags);
}

static int	only_white_space(char *str)
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
	ft_putstr_fd("command not found :", STDERR_FILENO);
	ft_putendl_fd(cmd_and_flags[0], STDERR_FILENO);
	return (127);
}

int	execute_cmd(char *paths[], char *arg_cmd, char *env[])
{
	char	*command;
	char	**cmd_and_flags;

	if (paths == NULL)
		return (perror("execute_cmd: paths is NULL"), -1);
	if (only_white_space(arg_cmd) == 1)
		arg_cmd = "cat";
	cmd_and_flags = ft_split(arg_cmd, ' ');
	if (cmd_and_flags == NULL) 
		return (perror("execute_cmd: ft_split failed"), -1);
	command = ft_strjoin("/", cmd_and_flags[0]);
	if (command == NULL)
	{
		free_paths(cmd_and_flags);
		perror("execute_cmd: strjoin failed");
		return (-1);
	}
	if (try_exec_paths(paths, command, cmd_and_flags, env) == 127)
	{
		free_command_and_flags(command, cmd_and_flags);
		exit(127);
	}
	return (free_command_and_flags(command, cmd_and_flags), -1);
}
