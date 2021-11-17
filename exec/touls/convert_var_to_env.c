
#include "../../includes/exec.h"

char	*getenv_var(char *str, int *index, char **env)
{
	int		i;
	int		start;
	char	*sbustr;
	char	*ret;

	start = *index;
	i = (*index);
	if (str[++i] == '?')
	{
		i++;
		*index = i;
		return (ft_itoa(0));
	}
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	*index = i;
	if ((start + 1) < i)
	{
		sbustr = ft_substr(str + 1, start, i - (start + 1));
		ret = ft_getenv_exec(env, sbustr);
		return (ret);
	}
	return (ft_substr(str, start, 1));
}

char	*convert_var_to_env(char *str, char **env, int fd)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			s = getenv_var(str + i, &i, env);
			ft_putstr_fd(s, fd);
			break;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
	return (s);
}