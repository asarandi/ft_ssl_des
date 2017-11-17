#include "../ft_printf/libftprintf.h"
#include "des.h"

typedef	unsigned long	t_ul;
typedef unsigned char	t_uc;

unsigned long	make_pc1(unsigned long k)
{
	unsigned long r = 0;
	unsigned long tmp = 0;
	unsigned long i = 0;

	r = 0;
	i = 0;
	while (i < sizeof(g_pc1_table))
	{
		tmp = (k >> (64 - g_pc1_table[i])) & 1;
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
	t_ul	before;
	t_ul	after;
	int		i;

	before = c_half << 28;
	before += d_half;
	i = 0;
	after = 0;
//	ft_printf("before pc2, two halves: %064lb\n", before);
	while (i < sizeof(g_pc2_table))
	{
		after <<= 1;
		after += ((before >> (56 - g_pc2_table[i])) & 1);
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
	unsigned long result;
	int	i;

	i = 0;
	result = 0;
	while (i < sizeof(g_ip1_table))
	{
		result <<= 1;
		result += (m >> (64 - g_ip1_table[i])) & 1;
		i++;
	}
	return (result);
}


t_ul	make_e(unsigned long r0)
{
	unsigned long result;
	unsigned long tmp;
	int i;

	i = 0;
	result = 0;
	while (i < sizeof(g_ebit_table))
	{
		tmp = r0 >> (32 - g_ebit_table[i]);
		tmp &= 1;
		result <<= 1;
		result += tmp;
		i++;
	}
	return (result);
}


unsigned long	get_s_boxes_value(unsigned long xor0)
{
	int		i;
	int		row;
	int		col;
	t_ul	tmp;
	t_ul	result;

	i = 0;
	result = 0;
	while(i < 8)
	{
		tmp = (xor0 >> (42 - (i * 6))) & 0x3f;
		row = ((tmp >> 4) & 2) + (tmp & 1);
		col = (tmp >> 1) & 0xf;
		tmp = g_s_boxes[i][(row * 16) + col];
		tmp <<= (28 - (i * 4));
		result += tmp;
		i++;
	}
	return (result);
}

unsigned long	make_pperm(unsigned long sb0)
{
	int				i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (i < 32)
	{
		result <<= 1;
		result += (sb0 >> (32 - g_pperm_table[i])) & 1;
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
	unsigned long er0;
	unsigned long sb0;
	unsigned long pp0;
	t_ul	l0;
	t_ul	r0;
	t_ul	r1;
	int	i;

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
	ft_printf("  key0 is %048lb\n", keys[0]);
//-----------------message-------------------//
	ft_printf("message is %064lb\n", m);
	m_ip = make_ip(m);
	ft_printf("  after ip %064lb\n", m_ip);



	l0 = (m_ip >> 32) & 0xffffffff;
	r0 = m_ip & 0xffffffff;

	i = 0;
	while (i < 16)
	{
//	ft_printf("L%02d is: %032lb\n", i, l0);
//	ft_printf("R%02d is: %032lb\n", i, r0);
		er0 = make_e(r0);
//	ft_printf("ER0 is: %048lb\n", er0); //48 bits
//	ft_printf("XOR is: %048lb\n", er0 ^ keys[i]);
		ft_printf("K%02d is %048lb\n",i ,keys[i]);
		sb0 = get_s_boxes_value(er0 ^ keys[i]);
//	ft_printf("SB0 is: %032lb\n", sb0);
		pp0 = make_pperm(sb0);
//	ft_printf("PP0 is: %032lb\n", pp0);
		r1 = l0 ^ pp0;
		l0 = r0;
		r0 = r1;
		i++;
	}
	ft_printf("L%02d is: %032lb\n",i, l0);
	ft_printf("R%02d is: %032lb\n",i, r1);


}
