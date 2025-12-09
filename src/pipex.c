/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 16:21:09 by dponte       #+#    #+#                  */
/*   Updated: 2025/12/02 14:19:12 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	int		ret;
	char	*infile;
	char	*outfile;
	char	**paths;

	if (argc < 4)
	{
		perror("Not enough arguments: ./program infile cmd1 cmd2 outfile");
		return (1);
	}
	if (empty_str_in_argv(argv))
		return (perror("No empty strings!"), 1);
	paths = extract_env(env);
	if (paths == NULL)
		return (perror("extract_env"), 1);
	infile = argv[1];
	outfile = argv[argc - 1];
	ret = main_loop(argc, argv, env, paths);
	if (ret == -1)
		strerror(errno);
	free_paths(paths);
	return (ret);
}
