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

//TODO: Handle errors
void	execute_cmd(char **paths, char *cmd, char **env)
{
	int		i;
	char	*path;

	if (paths == NULL)
		printf("error");
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], cmd);
		if (path == NULL)
			printf("error");
		if (access(path, F_OK) == 0)
			execve(path, &cmd, env);
		else
			free (path);
	}
}

//TODO: Attribute cmd
void	create_pipe(char **argv, char **paths, char **env)
{
	int		i;
	int		j;
	int		ret;
	int		pipefd[2];
	char	*cmd;

	// Create pipe
	pipe(pipefd);

	i = 2;
	j = 0;
	printf("0%d\n", pipefd[0]);
	printf("1%d\n", pipefd[1]);
	while (argv[i] != NULL)
	{
		printf("argv[i]: %s\n", argv[i]);
		printf("will exec\n");
		while (*paths[j])
		{
			printf("paths[i]: %s\n", paths[j]);
			execute_cmd(paths, cmd, env);
			printf("ret: %d\n", ret);
			j++;
		}
		printf("\n\nFinal ret: %d\n", ret);
		i++;
	}
}

//Need to define infile as stdin of the command
//Dup2 the result as stdin for the next function
// If it can't find a path it'll look for it in the current directory
