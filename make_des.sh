#!/bin/bash
gcc -g -L../ft_printf/ -lftprintf ecb.c des.c des_keys.c des_tables.c -o des1
