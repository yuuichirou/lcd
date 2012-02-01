#ifndef _macros_h_
#define _macros_h_


/* sfr_defs.h contains "#define _BV (bit) (1 <<(bit))" */
#define BIT(x) (1 << (x))


/* sets or clears more than one bit */
#define SETBITS(x,y)   ((x) |=   (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))


/* sets or clears only one bit */
#define SETBIT(x,y)   SETBITS  ((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))


/* check whether the bit is set BITSET or reset BITCLEAR
   similar macros bit_is_set and bit_is_clear contains sfr_defs.h
   returns zero or nonzero */
#define BITSET(x,y) ((x) & (BIT(y)))
#define BITCLEAR(x,y) !BITSET((x), (y))


/* returns zero or one
   after optimization no longer returns the value zero and one,
   only zero and nonzero */
#define BITVAL(x,y) (((x)>>(y)) & 1)


/* sets pin y of port x as input or output */
#define PIN_OUTPUT(x,y) SETBIT(_SFR_IO8(_SFR_IO_ADDR(x)-1), y)
#define PIN_INPUT(x,y)  CLEARBIT(_SFR_IO8(_SFR_IO_ADDR(x)-1), y)


/* sets more tahn one pin of port x as input or output */
#define PINS_OUTPUT(x,y) SETBITS(_SFR_IO8(_SFR_IO_ADDR(x)-1), y)
#define PINS_INPUT(x,y)  CLEARBITS(_SFR_IO8(_SFR_IO_ADDR(x)-1), y)


#define TRUE  1
#define FALSE 0


#define HI    1
#define LO    0

#endif
