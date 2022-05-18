#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	size_t			len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
