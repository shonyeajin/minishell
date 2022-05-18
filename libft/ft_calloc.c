#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	char	*p;
	size_t	i;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	p = mem;
	while (i < count * size)
	{
		*mem = 0;
		mem++;
		i++;
	}
	return (p);
}
