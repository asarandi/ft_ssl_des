#include "../ft_printf/libftprintf.h"

typedef	unsigned long	t_ul;
typedef unsigned char	t_uc;

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

unsigned long	circular_shift_left(unsigned long key, int bits)
{
	unsigned long	r;
	unsigned long	tmp;
	unsigned long	fullbits;

	tmp = bits;
	fullbits = 0;
	while (tmp--)
		fullbits = (fullbits << 1) + 1;
	tmp = (key >> (bits - 1)) & 1;
	r = ((key << 1) + tmp) & fullbits;
	return (r);
}

void	make_half_keys(t_ul half_keys[16], t_ul starter)
{
	char shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	int	i;
	char shift;
	t_ul newhalf;

	i = 0;
	while (i < 16)
	{
		shift = shifts[i];
		while (shift--)
		{
			newhalf = circular_shift_left(starter, 28);
			starter = newhalf;
		}
		half_keys[i] = newhalf;
		i++;
	}

	i = 0;
	while (i < 16)
	{
//		ft_printf("half key array index %02d, value %028lb\n", i, half_keys[i]);
		i++;
	}
}

t_ul	make_pc2(t_ul c_half, t_ul d_half)
{
	t_uc	pc2_table[] = {
                 14,    17,   11,    24,     1,    5,
                  3,    28,   15,     6,    21,   10,
                 23,    19,   12,     4,    26,    8,
                 16,     7,   27,    20,    13,    2,
                 41,    52,   31,    37,    47,   55,
                 30,    40,   51,    45,    33,   48,
                 44,    49,   39,    56,    34,   53,
                 46,    42,   50,    36,    29,   32};
	t_ul	before;
	t_ul	after;
	int		i;

	before = c_half << 28;
	before += d_half;
	i = 0;
	after = 0;
//	ft_printf("before pc2, two halves: %064lb\n", before);
	while (i < sizeof(pc2_table))
	{
		after <<= 1;
		after += ((before >> (56 - pc2_table[i])) & 1);
		i++;
	}
	return (after);
}

void	make_keys(t_ul keys[16], t_ul c_half[16], t_ul d_half[16])
{
	int	i;

	i = 0;
	while (i < 16)
	{
		keys[i] = make_pc2(c_half[i], d_half[i]);
//	ft_printf("       index %02d, key is %048lb\n", i, keys[i]);
		i++;
	}
}

t_ul	make_ip(unsigned long m)
{
	t_uc	ip_table[] = {
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7};
	
	unsigned long result;
	int	i;

	i = 0;
	result = 0;
	while (i < 64)
	{
		result <<= 1;
		result += (m >> (64 - ip_table[i])) & 1;
		i++;
	}
	return (result);
}


int main()
{
	unsigned long m = 0x0123456789ABCDEF;
	unsigned long m_ip;
	unsigned long k = 0x133457799BBCDFF1;
	unsigned long kp;
	unsigned long c0;
	unsigned long d0;

	unsigned long c_half_keys[16];
	unsigned long d_half_keys[16];
	unsigned long keys[16];
	t_ul	l0;
	t_ul	r0;

//	ft_printf("original %064lb\n", k);
	kp = make_pc1(k);
//	ft_printf("permuted %064lb\n", kp);
	c0 = kp >> 36;

	ft_printf("   c0 is %028lb\n", c0);
	d0 = (kp << 28) >> 36;
	ft_printf("   d0 is %028lb\n", d0);
	make_half_keys(c_half_keys, c0);
	make_half_keys(d_half_keys, d0);
	make_keys(keys, c_half_keys, d_half_keys);
//-----------------message-------------------//
	ft_printf("message is %064lb\n", m);
	m_ip = make_ip(m);
	ft_printf("  after ip %064lb\n", m_ip);
	l0 = (m_ip >> 32) & 0xffffffff;
	r0 = m_ip & 0xffffffff;
	ft_printf(" L0 is: %032lb\n", l0);
	ft_printf(" R0 is: %032lb\n", r0);

}
