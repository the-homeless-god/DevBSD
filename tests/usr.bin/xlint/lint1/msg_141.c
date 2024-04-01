/*	$NetBSD: msg_141.c,v 1.17 2024/03/27 20:09:43 rillig Exp $	*/
# 3 "msg_141.c"

// Test for message: '%s' overflows '%s' [141]

/* lint1-extra-flags: -h -X 351 */

// Integer overflow occurs when the arbitrary-precision result of an
// arithmetic operation cannot be represented by the type of the expression.

signed int s32;
unsigned int u32;
signed long long s64;
unsigned long long u64;
_Bool cond;

void
compl_s32(void)
{
	s32 = ~(-0x7fffffff - 1);
	s32 = ~-1;
	s32 = ~0;
	s32 = ~1;
	s32 = ~0x7fffffff;
}

void
compl_u32(void)
{
	u32 = ~0x00000000U;
	u32 = ~0x7fffffffU;
	u32 = ~0x80000000U;
	u32 = ~0xffffffffU;
}

void
compl_s64(void)
{
	s64 = ~(-0x7fffffffffffffffLL - 1LL);
	s64 = ~-1LL;
	s64 = ~0LL;
	s64 = ~0x7fffffffffffffffLL;
}

void
compl_u64(void)
{
	u64 = ~0ULL;
	u64 = ~0x7fffffffffffffffULL;
	u64 = ~0x8000000000000000ULL;
	u64 = ~0xffffffffffffffffULL;
}

void
uplus_s32(void)
{
	s32 = +(-0x7fffffff - 1);
	s32 = +-1;
	s32 = +0;
	s32 = +0x7fffffff;
}

void
uplus_u32(void)
{
	u32 = +0x00000000U;
	u32 = +0x7fffffffU;
	u32 = +0x80000000U;
	u32 = +0xffffffffU;
}

void
uplus_s64(void)
{
	s64 = +(-0x7fffffffffffffffLL - 1LL);
	s64 = +-1LL;
	s64 = +0LL;
	s64 = +0x7fffffffffffffffLL;
}

void
uplus_u64(void)
{
	u64 = +0x0000000000000000ULL;
	u64 = +0x7fffffffffffffffULL;
	u64 = +0x8000000000000000ULL;
	u64 = +0xffffffffffffffffULL;
}

void
uminus_s32(void)
{
	/* expect+1: warning: '-(-2147483648)' overflows 'int' [141] */
	s32 = -(-0x7fffffff - 1);
	s32 = - -1;
	s32 = -0;
	s32 = -0x7fffffff;
}

void
uminus_u32(void)
{
	u32 = -0x00000000U;
	u32 = -0x7fffffffU;
	u32 = -0x80000000U;
	u32 = -0xffffffffU;
}

void
uminus_s64(void)
{
	/* expect+1: warning: '-(-9223372036854775808)' overflows 'long long' [141] */
	s64 = -(-0x7fffffffffffffffLL - 1LL);
	s64 = - -1LL;
	s64 = -0LL;
	s64 = -0x7fffffffffffffffLL;
}

void
uminus_u64(void)
{
	u64 = -0x0000000000000000ULL;
	u64 = -0x7fffffffffffffffULL;
	u64 = -0x8000000000000000ULL;
	u64 = -0xffffffffffffffffULL;
}

void
mult_s32(void)
{
	/* expect+1: warning: '-65536 * 65536' overflows 'int' [141] */
	s32 = -0x00010000 * +0x00010000;	// -0x0100000000
	/* expect+1: warning: '-3 * 715827883' overflows 'int' [141] */
	s32 = -0x00000003 * +0x2aaaaaab;	// -0x80000001
	/* expect+1: warning: '715827883 * -3' overflows 'int' [141] */
	s32 = +0x2aaaaaab * -0x00000003;	// -0x80000001
	s32 = -0x00000008 * +0x10000000;	// -0x80000000
	s32 = +0x10000000 * -0x00000008;	// -0x80000000
	s32 = +0x00000002 * +0x3fffffff;	// +0x7ffffffe
	s32 = +0x3fffffff * +0x00000002;	// +0x7ffffffe
	s32 = +0x7fffffff * +0x00000001;	// +0x7fffffff
	s32 = +0x00000001 * +0x7fffffff;	// +0x7fffffff
	/* expect+1: warning: '2 * 1073741824' overflows 'int' [141] */
	s32 = +0x00000002 * +0x40000000;	// +0x80000000
	/* expect+1: warning: '1073741824 * 2' overflows 'int' [141] */
	s32 = +0x40000000 * +0x00000002;	// +0x80000000
	/* expect+1: warning: '65535 * 65537' overflows 'int' [141] */
	s32 = +0x0000ffff * +0x00010001;	// +0xffffffff
	/* expect+1: warning: '65536 * 65536' overflows 'int' [141] */
	s32 = +0x00010000 * +0x00010000;	// +0x0100000000
}

void
mult_u32(void)
{
	u32 = 0xffffU * 0x10001U;		// +0xffffffff
	/* expect+1: warning: '65536 * 65536' overflows 'unsigned int' [141] */
	u32 = 0x10000U * 0x10000U;		// +0x0100000000
}

void
mult_s64(void)
{
	/* expect+1: warning: '-4294967296 * 4294967296' overflows 'long long' [141] */
	s64 = -0x100000000LL * 0x100000000LL;	// -0x010000000000000000
	/* expect+1: warning: '-3 * 3074457345618258603' overflows 'long long' [141] */
	s64 = -3LL * 0x2aaaaaaaaaaaaaabLL;	// -0x8000000000000001
	/* expect+1: warning: '3074457345618258603 * -3' overflows 'long long' [141] */
	s64 = 0x2aaaaaaaaaaaaaabLL * -3LL;	// -0x8000000000000001
	s64 = -8LL * +0x1000000000000000LL;	// -0x8000000000000000
	s64 = +0x1000000000000000LL * -8LL;	// -0x8000000000000000
	s64 = +2LL * +0x3fffffffffffffffLL;	// +0x7ffffffffffffffe
	s64 = +0x3fffffffffffffffLL * +2LL;	// +0x7ffffffffffffffe
	s64 = +0x7fffffffffffffffLL * +1LL;	// +0x7fffffffffffffff
	s64 = +1LL * +0x7fffffffffffffffLL;	// +0x7fffffffffffffff
	/* expect+1: warning: '2 * 4611686018427387904' overflows 'long long' [141] */
	s64 = +2LL * +0x4000000000000000LL;	// +0x8000000000000000
	/* expect+1: warning: '4611686018427387904 * 2' overflows 'long long' [141] */
	s64 = +0x4000000000000000LL * +2LL;	// +0x8000000000000000
	/* expect+1: warning: '4294967295 * 4294967297' overflows 'long long' [141] */
	s64 = +0xffffffffLL * +0x100000001LL;	// +0xffffffffffffffff
	/* expect+1: warning: '4294967296 * 4294967296' overflows 'long long' [141] */
	s64 = +0x100000000LL * +0x100000000LL;	// +0x010000000000000000
}

void
mult_u64(void)
{
	u64 = 0xffffffffULL * 0x100000001ULL;	// +0xffffffffffffffff
	u64 = 0x00010000ULL * 0x00010000ULL;	// +0x0100000000
	/* expect+1: warning: '4294967296 * 4294967296' overflows 'unsigned long long' [141] */
	u64 = 0x100000000ULL * 0x100000000ULL;	// +0x010000000000000000
}

void
div_s32(void)
{
	/* expect+1: warning: '-2147483648 / -1' overflows 'int' [141] */
	s32 = (-0x7fffffff - 1) / -1;
	s32 = (-0x7fffffff - 1) / 1;
	s32 = 0x7fffffff / -1;
	/* expect+1: error: division by 0 [139] */
	s32 = 0 / 0;
	/* expect+1: error: division by 0 [139] */
	s32 = 0x7fffffff / 0;
}

void
div_u32(void)
{
	u32 = 0xffffffffU / -1U;
	u32 = 0xffffffffU / 1U;
	/* expect+1: error: division by 0 [139] */
	u32 = 0U / 0U;
	/* expect+1: error: division by 0 [139] */
	u32 = 0xffffffffU / 0U;
}

void
div_s64(void)
{
	/* expect+1: warning: '-9223372036854775808 / -1' overflows 'long long' [141] */
	s64 = (-0x7fffffffffffffffLL - 1LL) / -1LL;
	s64 = (-0x7fffffffffffffffLL - 1LL) / 1LL;
	s64 = (-0x7fffffffffffffffLL - 1LL) / 0x7fffffffffffffffLL;
	s64 = 0x7fffffffffffffffLL / -1LL;
	s64 = (-0x7fffffffLL - 1LL) / -1LL;
	s64 = (-0x7fffffffLL - 1LL) / 0x7fffffffLL;
	/* expect+1: error: division by 0 [139] */
	s64 = 0LL / 0LL;
	/* expect+1: error: division by 0 [139] */
	s64 = 0x7fffffffffffffffLL / 0LL;
}

void
div_u64(void)
{
	u64 = 0xffffffffffffffffULL / -1ULL;
	u64 = 0xffffffffffffffffULL / 1ULL;
	/* expect+1: error: division by 0 [139] */
	u64 = 0ULL / 0ULL;
	/* expect+1: error: division by 0 [139] */
	u64 = 0xffffffffffffffffULL / 0ULL;
}

void
mod_s32(void)
{
	s32 = -1 % (-0x7fffffff - 1);
	s32 = -1 % 0x7fffffff;
	/* expect+1: warning: '-2147483648 % -1' overflows 'int' [141] */
	s32 = (-0x7fffffff - 1) % -1;
	s32 = 0x7fffffff % -1;
}

void
mod_u32(void)
{
	u64 = 0xffffffffU % -1U;
	u64 = 0xffffffffU % 1U;
	/* expect+1: error: modulus by 0 [140] */
	u64 = 0U % 0U;
	/* expect+1: error: modulus by 0 [140] */
	u64 = 0xffffffffU % 0U;
}

void
mod_s64(void)
{
	s64 = -1LL % (-0x7fffffffffffffffLL - 1LL);
	s64 = -1LL % 0x7fffffffffffffffLL;
	/* expect+1: warning: '-9223372036854775808 % -1' overflows 'long long' [141] */
	s64 = (-0x7fffffffffffffffLL - 1LL) % -1LL;
	s64 = 0x7fffffffffffffffLL % -1LL;
}

void
mod_u64(void)
{
	u64 = 0xffffffffffffffffULL % -1ULL;
	u64 = 0xffffffffffffffffULL % 1ULL;
	/* expect+1: error: modulus by 0 [140] */
	u64 = 0ULL % 0ULL;
	/* expect+1: error: modulus by 0 [140] */
	u64 = 0xffffffffffffffffULL % 0ULL;
}

void
plus_s32(void)
{
	/* expect+1: warning: '-2147483647 + -2147483647' overflows 'int' [141] */
	s32 = -0x7fffffff + -0x7fffffff;
	/* expect+1: warning: '-2147483647 + -2' overflows 'int' [141] */
	s32 = -0x7fffffff + -2;			// INT_MIN - 1
	/* expect+1: warning: '-2 + -2147483647' overflows 'int' [141] */
	s32 = -2 + -0x7fffffff;			// INT_MIN - 1
	s32 = -0x7fffffff + -1;			// INT_MIN
	s32 = -1 + -0x7fffffff;			// INT_MIN
	s32 = -0x7fffffff + 0;			// INT_MIN + 1
	s32 = 0 + -0x7fffffff;			// INT_MIN + 1
	s32 = (-0x7fffffff - 1) + 0x7fffffff;	// -1
	s32 = 0x7fffffff + (-0x7fffffff - 1);	// -1
	s32 = 0x7ffffffe + 1;			// INT_MAX
	s32 = 1 + 0x7ffffffe;			// INT_MAX
	s32 = 0x7fffffff + 0;			// INT_MAX
	s32 = 0 + 0x7fffffff;			// INT_MAX
	/* expect+1: warning: '2147483647 + 1' overflows 'int' [141] */
	s32 = 0x7fffffff + 1;			// INT_MAX + 1
	/* expect+1: warning: '1 + 2147483647' overflows 'int' [141] */
	s32 = 1 + 0x7fffffff;			// INT_MAX + 1
	/* expect+1: warning: '1073741824 + 1073741824' overflows 'int' [141] */
	s32 = 0x40000000 + 0x40000000;		// INT_MAX + 1
	/* expect+1: warning: '2147483647 + 2147483647' overflows 'int' [141] */
	s32 = 0x7fffffff + 0x7fffffff;
}

void
plus_u32(void)
{
	u32 = 0x00000000U + 0x00000000U;
	u32 = 0x40000000U + 0x40000000U;
	u32 = 0xffffffffU + 0x00000000U;
	u32 = 0x00000000U + 0xffffffffU;
	u32 = 0xfffffffeU + 0x00000001U;
	/* expect+1: warning: '4294967295 + 1' overflows 'unsigned int' [141] */
	u32 = 0xffffffffU + 0x00000001U;
	/* expect+1: warning: '1 + 4294967295' overflows 'unsigned int' [141] */
	u32 = 0x00000001U + 0xffffffffU;
	/* expect+1: warning: '4294967295 + 4294967295' overflows 'unsigned int' [141] */
	u32 = 0xffffffffU + 0xffffffffU;
}

void
plus_s64(void)
{
	/* expect+1: warning: '-9223372036854775807 + -2' overflows 'long long' [141] */
	s64 = -0x7fffffffffffffffLL + -2LL;
	s64 = -0x7fffffffffffffffLL + -1LL;
	s64 = 0x7ffffffffffffffeLL + 1LL;
	/* expect+1: warning: '9223372036854775807 + 1' overflows 'long long' [141] */
	s64 = 0x7fffffffffffffffLL + 1LL;
}

void
plus_u64(void)
{
	u64 = 0x0000000000000000ULL + 0x0000000000000000ULL;
	u64 = 0xffffffffffffffffULL + 0x0000000000000000ULL;
	u64 = 0x0000000000000000ULL + 0xffffffffffffffffULL;
	u64 = 0xfffffffffffffffeULL + 0x0000000000000001ULL;
	/* expect+1: warning: '18446744073709551615 + 1' overflows 'unsigned long long' [141] */
	u64 = 0xffffffffffffffffULL + 0x0000000000000001ULL;
	/* expect+1: warning: '1 + 18446744073709551615' overflows 'unsigned long long' [141] */
	u64 = 0x0000000000000001ULL + 0xffffffffffffffffULL;
	/* expect+1: warning: '18446744073709551615 + 18446744073709551615' overflows 'unsigned long long' [141] */
	u64 = 0xffffffffffffffffULL + 0xffffffffffffffffULL;
}

void
minus_s32(void)
{
	/* expect+1: warning: '-2147483647 - 2' overflows 'int' [141] */
	s32 = -0x7fffffff - 2;
	s32 = -0x7fffffff - 1;
	s32 = -0x7fffffff - 1 - 0;
	s32 = -0x7fffffff - 1 - -1;
	s32 = 0x7fffffff - 0x7fffffff;
	s32 = 0x7fffffff - 1;
	s32 = 0x7fffffff - 0;
	/* expect+1: warning: '2147483647 - -1' overflows 'int' [141] */
	s32 = 0x7fffffff - -1;
}

void
minus_u32(void)
{
	u32 = 0x00000000U - 0x00000000U;
	/* expect+1: warning: '0 - 1' overflows 'unsigned int' [141] */
	u32 = 0x00000000U - 0x00000001U;
	/* expect+1: warning: '0 - 2147483648' overflows 'unsigned int' [141] */
	u32 = 0x00000000U - 0x80000000U;
	u32 = 0x80000000U - 0x00000001U;
	/* expect+1: warning: '0 - 4294967295' overflows 'unsigned int' [141] */
	u32 = 0x00000000U - 0xffffffffU;
	u32 = 0xffffffffU - 0x00000000U;
	u32 = 0xffffffffU - 0xffffffffU;
}

void
minus_s64(void)
{
	/* expect+1: warning: '-9223372036854775807 - 9223372036854775807' overflows 'long long' [141] */
	s64 = -0x7fffffffffffffffLL - 0x7fffffffffffffffLL;
	/* expect+1: warning: '-9223372036854775807 - 2' overflows 'long long' [141] */
	s64 = -0x7fffffffffffffffLL - 2LL;
	s64 = -0x7fffffffffffffffLL - 1LL;
	s64 = -0x7fffffffffffffffLL - 0LL;
	s64 = -0x7fffffffffffffffLL - -1LL;
	s64 = 0x7fffffffffffffffLL - 1LL;
	s64 = 0x7fffffffffffffffLL - 0LL;
	/* expect+1: warning: '9223372036854775807 - -1' overflows 'long long' [141] */
	s64 = 0x7fffffffffffffffLL - -1LL;
	/* expect+1: warning: '9223372036854775807 - -9223372036854775807' overflows 'long long' [141] */
	s64 = 0x7fffffffffffffffLL - -0x7fffffffffffffffLL;
}

void
minus_u64(void)
{
	u64 = 0x0000000000000000ULL - 0x0000000000000000ULL;
	/* expect+1: warning: '0 - 1' overflows 'unsigned long long' [141] */
	u64 = 0x0000000000000000ULL - 0x0000000000000001ULL;
	/* expect+1: warning: '0 - 9223372036854775808' overflows 'unsigned long long' [141] */
	u64 = 0x0000000000000000ULL - 0x8000000000000000ULL;
	u64 = 0x8000000000000000ULL - 0x0000000000000001ULL;
	/* expect+1: warning: '0 - 18446744073709551615' overflows 'unsigned long long' [141] */
	u64 = 0x0000000000000000ULL - 0xffffffffffffffffULL;
	u64 = 0xffffffffffffffffULL - 0x0000000000000000ULL;
	u64 = 0xffffffffffffffffULL - 0xffffffffffffffffULL;
}

void
shl_s32(void)
{
	/* expect+1: warning: '256 << 23' overflows 'int' [141] */
	s32 = 0x0100 << 23;
	/* expect+1: warning: '256 << 24' overflows 'int' [141] */
	s32 = 0x0100 << 24;
	/* expect+1: warning: shift amount 18446744073709551615 is greater than bit-size 32 of 'int' [122] */
	s32 = 0 << 0xffffffffffffffff;
}

void
shl_u32(void)
{
	u32 = 0x0100U << 23;
	/* expect+1: warning: '256 << 24' overflows 'unsigned int' [141] */
	u32 = 0x0100U << 24;
	/* expect+1: warning: negative shift [121] */
	u32 = 0x0000U << -1;
	/* expect+1: warning: shift amount 256 is greater than bit-size 32 of 'unsigned int' [122] */
	u32 = 0x0100U << 0x0100U;
	/* expect+1: warning: shift amount 4294967295 is greater than bit-size 32 of 'unsigned int' [122] */
	u32 = 0x0100U << 0xffffffffU;
	/* expect+1: warning: shift amount 18446744073709551615 is greater than bit-size 32 of 'unsigned int' [122] */
	u32 = 0x0100U << 0xffffffffffffffffULL;
}

void
shl_s64(void)
{
	s64 = 1LL << 62;
	s64 = 1LL << 63;
	/* expect+1: warning: shift amount 64 equals bit-size of 'long long' [267] */
	s64 = 1LL << 64;
}

void
shl_u64(void)
{
	s64 = 1ULL << 62;
	s64 = 1ULL << 63;
	/* expect+1: warning: shift amount 64 equals bit-size of 'unsigned long long' [267] */
	s64 = 1ULL << 64;
}

void
shr_s32(void)
{
	s32 = -0x7fffffff >> 1;
	s32 = -10 >> 1;
	s32 = -9 >> 1;
	s32 = +9 >> 1;
	s32 = +10 >> 1;
	s32 = 0x7fffffff >> 1;

	/* expect+1: error: negative array dimension (-16) [20] */
	typedef int minus_32_shr_1[-32 >> 1];
	/* expect+1: error: negative array dimension (-16) [20] */
	typedef int minus_31_shr_1[-31 >> 1];
	/* expect+1: error: negative array dimension (-15) [20] */
	typedef int minus_30_shr_1[-30 >> 1];
	/* expect+1: error: negative array dimension (-1) [20] */
	typedef int minus_1_shr_1[-1 >> 31];
}

void
shr_u32(void)
{
	u32 = 0xffffffffU >> 1;
	/* expect+1: warning: shift amount 32 equals bit-size of 'unsigned int' [267] */
	u32 = 0xffffffffU >> 32;
	u32 = 0x00000000U >> 1;
}

void
shr_s64(void)
{
	// TODO

	/* expect+1: error: negative array dimension (-16) [20] */
	typedef int minus_16_shr_0[-16LL >> 0];
	/* expect+1: error: negative array dimension (-8) [20] */
	typedef int minus_16_shr_1[-16LL >> 1];
	/* expect+1: error: negative array dimension (-1) [20] */
	typedef int minus_16_shr_16[-16LL >> 16];
	/* expect+1: error: negative array dimension (-1) [20] */
	typedef int minus_16_shr_40[-16LL >> 40];
}

void
shr_u64(void)
{
	// TODO
}

void
compare_s32(void)
{
	cond = 0x7fffffff <  (-0x7fffffff - 1);
	cond = 0x7fffffff <= (-0x7fffffff - 1);
	cond = 0x7fffffff >  (-0x7fffffff - 1);
	cond = 0x7fffffff >= (-0x7fffffff - 1);
	cond = 0x7fffffff == (-0x7fffffff - 1);
	cond = 0x7fffffff != (-0x7fffffff - 1);
}

void
compare_u32(void)
{
	cond = 0xffffffffU <  0x00000000U;
	cond = 0xffffffffU <= 0x00000000U;
	cond = 0xffffffffU >  0x00000000U;
	cond = 0xffffffffU >= 0x00000000U;
	cond = 0xffffffffU == 0x00000000U;
	cond = 0xffffffffU != 0x00000000U;
}

void
compare_s64(void)
{
	cond = 0x7fffffffffffffffLL <  (-0x7fffffffffffffffLL - 1);
	cond = 0x7fffffffffffffffLL <= (-0x7fffffffffffffffLL - 1);
	cond = 0x7fffffffffffffffLL >  (-0x7fffffffffffffffLL - 1);
	cond = 0x7fffffffffffffffLL >= (-0x7fffffffffffffffLL - 1);
	cond = 0x7fffffffffffffffLL == (-0x7fffffffffffffffLL - 1);
	cond = 0x7fffffffffffffffLL != (-0x7fffffffffffffffLL - 1);
}

void
compare_u64(void)
{
	cond = 0xffffffffffffffffULL <  0x0000000000000000ULL;
	cond = 0xffffffffffffffffULL <= 0x0000000000000000ULL;
	cond = 0xffffffffffffffffULL >  0x0000000000000000ULL;
	cond = 0xffffffffffffffffULL >= 0x0000000000000000ULL;
	cond = 0xffffffffffffffffULL == 0x0000000000000000ULL;
	cond = 0xffffffffffffffffULL != 0x0000000000000000ULL;
}

void
bitand_s32(void)
{
	s32 = 0x55555555 & -0xff;
}

void
bitand_u32(void)
{
	u32 = 0xffffffffU & 0x55555555U;
	u32 = 0x55555555U & 0xaaaaaaaaU;
}

void
bitand_s64(void)
{
	u64 = ~0x7fffeeeeddddccccLL & 0x1111222233334444LL;
}

void
bitand_u64(void)
{
	u64 = 0xffffeeeeddddccccULL & 0x1111222233334444ULL;
}

void
bitxor_s32(void)
{
	s32 = 0x12345678 ^ 0x76543210;
}

void
bitxor_u32(void)
{
	u32 = 0xffffffffU ^ 0x55555555U;
	u32 = 0x55555555U ^ 0xaaaaaaaaU;
}

void
bitxor_s64(void)
{
	s64 = ~0x123456789abcdef0LL ^ 0x0123456789abcdefLL;
}

void
bitxor_u64(void)
{
	u64 = 0xfedcba9876543210ULL ^ 0x0123456789abcdefULL;
}

void
bitor_s32(void)
{
	s32 = 0x3333cccc | 0x5555aaaa;
}

void
bitor_u32(void)
{
	u32 = 0xffffffffU | 0x00000000U;
	u32 = 0xffffffffU | 0xffffffffU;
	u32 = 0x55555555U | 0xaaaaaaaaU;
}

void
bitor_s64(void)
{
	s64 = 0x1111222233334444LL | ~0x0000111122223333LL;
}

void
bitor_u64(void)
{
	u64 = 0x1111222233334444ULL | 0xffffeeeeddddccccULL;
}
