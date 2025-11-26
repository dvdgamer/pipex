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
#include <stdio.h>

/*
 * extract_env:
 * - Scans the environment array `env` for the PATH entry.
 * - Returns a newly-allocated NULL-terminated array of directory strings
 *   (as produced by `ft_split`) containing PATH components, or NULL if
 *   PATH is not found or `env` is NULL.
 * - Caller is responsible for freeing the returned array and its strings.
 */
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

/*
 * try_exec_paths:
 * - Iterates `paths`, concatenates each entry with `command` and tries
 *   to execve() the resulting path. On execve() error it logs the
 *   per-path failure and continues. Returns -1 if no exec succeeded.
 *
 * Notes:
 * - execve() replaces the process image on success and does not return.
 *   Therefore this helper does not free `command` or `cmd_and_flags` when
 *   calling execve(). If execve() returns it failed for that candidate and
 *   the helper continues to the next path.
 */

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

/*
 * execute_cmd:
 * - paths: NULL-terminated array of directory strings (from PATH).
 * - arg_cmd: a command string as provided on the command line
 *   (e.g. "grep h").
 * - env: environment array to pass to execve.
 *
 * Behavior:
 * - Splits arg_cmd into argv-style array (`ft_split`), prepends '/' to the
 *   command name, and tries each directory in `paths` by concatenating
 *   path + '/' + command. If `access(path_to_exec, F_OK)` succeeds,
 *   calls execve(path_to_exec, cmd_and_flags, env).
 * - On success execve() does not return. On failure, returns -1.
 *
 * Resource ownership:
 * - This function allocates `cmd_and_flags` and `command`; it frees them
 *   before returning. If you change the function to early-return, ensure
 *   allocated memory is freed.
 *
 * Error handling:
 * - If `paths` is NULL, prints an error message and returns -1.
 */
int	execute_cmd(char *paths[], char *arg_cmd, char *env[])
{
	char	*command;
	char	**cmd_and_flags;

	if (paths == NULL)
		return (perror("execute_cmd: paths is NULL"), -1);
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
