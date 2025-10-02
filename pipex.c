/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/09 16:03:22 by dponte       #+#    #+#                  */
/*   Updated: 2025/07/09 16:16:54 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

// < file1 cmd1 | cmd2 > file2
//
// < infile grep ac | wc -c
// 		==
// grep ac < infile | wc -c

// < is the "input redirection" symbol
// redirects the contents of infile to standard input
// This reads the file via stdin instead of dirctly opening the file

// pipe |
// directs the output on the left of operator to stdin to the right

// > output redirection
// points the stdout into the designated file
// replaces the contents of the receiving file

// >> appends the output to the designated file
//
// << symbol is an input "redirection" symbol
//It makes the shell read from the standard input until it encounters only a specific LIMITER on the stdin.
//LIMITER is the here document or 'heredoc'
//
//cmd << LIMITER | cmd1 >> file
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include "pipex.h"
#include "libft/libft.h"

/*
 * Gets the env varabiables
 * Trims the first env_var to remove the "PATH ="
 */
char **extract_env(char *env[])
{
	int i;
	int j;
	char *env_var;
	char **env_paths;

	i = 0;
	while (env[i] != NULL)
	{
		env_var = ft_substr(env[i], 0, 4);
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

int main (int argc, char *argv[], char *env[])
{
	int i = 0;
	// pid is the id of the child process
	int pid = fork();
	char **env_list = extract_env(env);

	for (i = 0; env_list[i]; i++)
	{
		printf("Split[%d]:%s\n", i, env_list[i]);
	}
	/* for (i = 0; env_list[i]; i++) */
	/* 	free(env_list[i]); */
	/* free(env_list); */
	if (pid == 0)
		//callchildfunction(i);
		printf("hello from child process %d\n", pid);
	else if (pid == -1)
		/* error(); */
		printf("error\n");
	else
		/* parentfunc(pid); */
		printf("hello from parent process %d\n", pid);
	/* wait(); */
	/* waitpid(); */
	/* accessexit(); */
};

