#include <stdio.h>

int main()
{
	FILE *fp_in, *fp_out;
	int c;
	int ret;

	fp_in = fopen("a.pdf", "r");
	if (NULL == fp_in)
	{
		perror("fopen");
		return -1;
	}
	
	fp_out = fopen("b.pdf", "w");
	if (NULL == fp_out)
	{
		perror("fopen");
		return -1;
	}

	while (1)
	{
		c = fgetc(fp_in);
		if (EOF == c)
		{
			break;
		}
		
		ret = fputc(c, fp_out);
		if (EOF == ret)
		{
			perror("fputc");
			return -1;
		}
	}

	return 0;
}
