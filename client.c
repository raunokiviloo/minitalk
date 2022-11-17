#include <stdio.h>

int main (int argc, char **argv)
{
	char *str;
	int bits[8];
	int	bit_index;

	if (argc != 3)
	{
		printf("ERROR. Usage: ./client <server PID> <string>");
		return (1);
	}
	str = argv[2];
	while (*str)
	{
		bit_index = 0;
		while (bit_index < 8)
		{
			bits[7 - bit_index] = (*str >> bit_index) & 1;
			bit_index++;
		}
		/*for (int i = 0; i < 8; i++)
			printf("%i", bits[i]);*/
		str++;
	}
}