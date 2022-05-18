#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (size < dstsize && dst[size])
		size++;
	if (size < dstsize)
	{
		while (src[i] && (i + size + 1) < dstsize)
		{
			dst[size + i] = src[i];
			i++;
		}
		dst[size + i] = 0;
	}
	return (size + ft_strlen(src));
}
