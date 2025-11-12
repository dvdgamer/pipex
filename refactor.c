/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   refactor.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/11/12 16:21:09 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 18:39:56 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*infile;
	char	*outfile;
	char	**paths;

	paths = extract_env(env);
	if (argc < 4 || empty_str_in_argv(argv))
		return (perror("No empty strings!"), free(paths), 1);
	infile = argv[1];
	outfile = argv[argc - 1];
	if (access(infile, F_OK) == -1)
		return (perror("infile"), 1);
	main_loop(argc, argv, env, paths);
	free(paths);
	return (0);
}
