
#include "../../includes/exec.h"

void	split_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	*ft_getenv_exec(char **env, char *name)
{
	char	*ret;
	char	**content;
	int		i;

	i = 0;
	if (!env || !name)
		return (NULL);
	while (env[i])
	{
		content = ft_split(env[i], '=');
		if (!ft_strcmp(content[0], name))
			break ;
		split_free(content);
		i++;
	}
	if (!env[i])
		return (NULL);
	ret = ft_strdup(content[1]);
	split_free(content);
	return (ret);
}