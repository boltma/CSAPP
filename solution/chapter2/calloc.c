#include <stdlib.h>
#include <string.h>

void *another_calloc(size_t nmemb, size_t size)
{
	if (!nmemb || !size)
		return NULL;
	size_t buf_size = nmemb * size;
	if (buf_size / size == nmemb)
	{
		void* buf = malloc(buf_size);
		memset(buf, 0, buf_size);
		return buf;
	}
	else
		return NULL;
}
