#include "../ft_printf/libftprintf.h"



unsigned long	make_pc1(unsigned long k)
{
	unsigned long r = 0;
	unsigned long tmp = 0;
	unsigned long i = 0;

	unsigned long pc1_table[] = {
              57,   49,    41,   33,    25,    17,    9,
               1,   58,    50,   42,    34,    26,   18,
              10,    2,    59,   51,    43,    35,   27,
              19,   11,     3,   60,    52,    44,   36,
              63,   55,    47,   39,    31,    23,   15,
               7,   62,    54,   46,    38,    30,   22,
              14,    6,    61,   53,    45,    37,   29, 
              21,   13,     5,   28,    20,    12,    4};
	r = 0;
	i = 0;
	while (i < 56)
	{
		tmp = (k >> (64 - pc1_table[i])) & 1;
		tmp = tmp << (63 - i);
		r += tmp;
		i++;
	}
	return (r);
}


void	make_cds(unsigned long keys[16])
{
	char shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
}


int main()
{
	unsigned long k = 0x133457799BBCDFF1;
	unsigned long kp;
	unsigned long c0;
	unsigned long d0;

	unsigned long c_keys[16];
	unsigned long d_keys[16];


	ft_printf("original %064lb\n", k);
	kp = make_pc1(k);
	ft_printf("permuted %064lb\n", kp);
	c0 = kp >> 36;
	ft_printf("   c0 is %028lb\n", c0);
	d0 = (kp << 28) >> 36;
	ft_printf("   d0 is %028lb\n", d0);
	c_keys[0] = c0;
	d_keys[0] = d0;

}
