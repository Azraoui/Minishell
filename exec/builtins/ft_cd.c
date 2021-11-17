
#include "../../includes/exec.h"

int	chdir_help2(char **env, char **old_path, char **new_path)
{
	*old_path = ft_getenv_exec(env, "PWD");
	if (*old_path == NULL)
		*old_path = ft_strdup("");
	if (chdir(*new_path) == -1)
	{
		free(*new_path);
		return (ft_perror(*new_path, ": No such file or directory", 1));
	}
	free(*new_path);
	*new_path = getcwd(NULL, 1000);
	return (0);
}

int	ft_chdir(char **args, char **env, char **new_path, char **old_path)
{
	if (!*(args + 1))
	{
		*new_path = ft_getenv_exec(env, "HOME");
		if (!*new_path)
			return (ft_perror(*args, ": HOME not set", 1));
	}
	else
		*new_path = ft_strdup(args[1]);
	*old_path = getcwd(NULL, 1000);
	return (chdir_help2(env, old_path, new_path));
}

int ft_cd(char **args, char ***env)
{
	char	*new_path;
	char	*old_path;
	char	**arr;
	int		ret;

	arr = (char **)malloc(sizeof(char *) * 4);
	ret = ft_chdir(args, *env, &new_path, &old_path);
	if (!ret)
	{
		arr[0] = NULL;
		arr[1] = ft_strdup(ft_strjoin("OLDPWD=", old_path));
		arr[2] = ft_strdup(ft_strjoin("PWD=", new_path));
		arr[3] = NULL;
		ft_export(arr, env, 1);
		split_free(arr);
	}
	return (ret);
}
