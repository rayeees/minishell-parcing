#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] && s2[i] && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}


char	*ft_strjoin(char *s1, char *s2)
{
	int		lens1;
	char	*str;
	int		i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (s2);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) +1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	lens1 = 0;
	while (s2[lens1])
	{
		str[i] = ((char *)s2)[lens1];
		i++;
		lens1++;
	}
	str[i] = '\0';
	return (str);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	unsigned int	size_sub_str;

	i = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	size_sub_str = min(ft_strlen(s) - start, len);
	str = malloc((size_sub_str + 1));
	if (str == 0)
		return (NULL);
	while (i < size_sub_str)
	{
		str[i] = s[i + start];
		i++; 
	}
	str[i] = '\0';
	return (str);
}

char    *ft_find_in_path(char **env, char *str)
{
    char    *save;
    char    *arg;
    int i;
    int j;

    j = 0;
    i = 0;
    arg = ft_strjoin(str, "=");
    while (env[i])
    {
        j = ft_strncmp(env[i], arg, ft_strlen(arg));
        if(!j)
            break;
        i++;
    }
    if (!j)
        save = ft_substr(env[i], ft_strlen(arg), ft_strlen(env[i] + 5));
    else
        save = "";
    return (save);
}

// int main(int argc, char **argv, char **env)
// {
//     (void) argc;
//     printf("%s\n", ft_find_in_path(env, argv[1]));
// }