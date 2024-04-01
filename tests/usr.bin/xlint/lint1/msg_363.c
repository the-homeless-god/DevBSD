/*	$NetBSD: msg_363.c,v 1.4 2024/03/03 16:09:01 rillig Exp $	*/
# 3 "msg_363.c"

// Test for message: non-printing character '%.*s' in description '%.*s' [363]

/*
 * The purpose of snprintb is to produce a printable, visible representation
 * of a binary number, therefore the description should consist of visible
 * characters only.
 */

/* lint1-extra-flags: -X 351 */

typedef typeof(sizeof(0)) size_t;
typedef unsigned long long uint64_t;

int snprintb(char*, size_t, const char*, uint64_t);

void
old_style_description(unsigned u32)
{
	char buf[64];

	/* expect+6: warning: bit position '\t' in '\tprint' should be escaped as octal or hex [369] */
	/* expect+5: warning: non-printing character '\377' in description 'able\377' [363] */
	/* expect+4: warning: bit position '\n' in '\nable\377' should be escaped as octal or hex [369] */
	snprintb(buf, sizeof(buf),
	    "\020"
	    "\001non\tprint\nable\377",
	    u32);

	/* expect+10: warning: non-printing character '\177' in description '\177' [363] */
	/* expect+9: warning: non-printing character '\177' in description 'aa""""\177' [363] */
	/* expect+8: warning: non-printing character '\177' in description 'bb""\177' [363] */
	/* expect+7: warning: non-printing character '\177' in description 'cc\177' [363] */
	snprintb(buf, sizeof(buf),
	    "\020"
	    "\002""\177"
	    "\003aa""""\177"
	    "\004""bb""\177"
	    "\005""""cc\177",
	    u32);

	/* expect+6: warning: bit position '\000' (0) in '\000print' out of range 1..32 [371] */
	/* expect+5: warning: bit position '\n' in '\nable' should be escaped as octal or hex [369] */
	/* expect+4: warning: redundant '\0' at the end of the format [377] */
	snprintb(buf, sizeof(buf),
	    "\020"
	    "\001non\000print\nable\0",
	    u32);
}
