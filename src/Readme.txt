Single Precision Floating Point Routines for the Z80
Zeda Thomas (xedaelnara@gmail.com)
%=%=%=%=%=%=%=%=%=%=%
0.0 Table of Contents
%=%=%=%=%=%=%=%=%=%=%
  0.0 Table of Contents
  0.1 License
  0.2 Usage and Setup
  0.3 Formats
  1.0 Special Constants
  2.0 Routines
  2.1 Math
  2.2 Convert
  3.0 Examples
  4.0 Log
  5.0 To Do
  6.0 Bugs

%=%=%=%=%=%=%
0.1 License
%=%=%=%=%=%=%
  I am particularly proud of these routines. If you are using these routines, then I ask that you credit me in public releases.
  Whether it is in the source or the readme, I don't mind
      Examples of sufficient credit:
        -This license or readme.
        -"Zeda's routines. If there are undocumented bugs, let her know."
        -"Zeda's Single Precision Floating-Point Routines."
        -"credit- Zeda Thomas"
    Contact me before using these routines for profit.
    My code cannot be further restricted by additional license except at my approval.
  When in doubt, ask! I sometimes go weeks or months without checking email or
social media. If waiting for me is impeding a release, you can release it and
we can discuss it later.

%=%=%=%=%=%=%=%=%=%
0.2 Usage and Setup
%=%=%=%=%=%=%=%=%=%
  In order to use these routines, just '#include "<<routine>>.z80"' and any dependencies.
  You may also want to change the value for 'scrap' which is used for calculations.
  All the routines included have a standard input/output:
    HL points to the first argument known as 'x'
    DE points to the second argument known as 'y', when required.
    BC points to where the result is output.
  If you want to include specific routines, just include that file. For example,
suppose you want to use addSingle, subSingle, mulSingle, divSingle, and single2str.
Then you would do:
    |#define scrap 8000h
    |#include "addSingle.z80"   ;includes addSingle and subSingle, as well as rsubSingle.
    |#include "mulSingle.z80"   ;Also includes mul10Single
    |#include "divSingle.z80"   ;Also includes invSingle
    |#include "single2str.z80"

%=%=%=%=%=%
0.3 Formats
%=%=%=%=%=%
  Floats are stored first with a little-endian 24-bit mantissa. However, the highest bit
is taken as implicitly 1, so we replace it as a sign bit. Next comes an 8-bit
exponent biased by +128.
  Wat? Suppose we had 1.1101 * 2^3 in base 2 scientific notation. Then:
    mantissa = 1.11010000000000000000000
    exponent = 3
    sign     = +
  Because of the nature of scientific notation, the mantissa can never be less
than 1.0 except in the special case of ZERO. However, because it is base-2
scientific notation, the integer part cannot be more than 1. This means the
integer part is always 1, excepting special cases. So why waste space storing it?
Instead, we will substitute that bit with the sign flag. 0 is +, 1 is -.
  Putting it together a little more:
    mantissa = +.11010000000000000000000
            ==> 01101000 00000000 00000000
      little endian
            ==> 00000000 00000000 01101000
            ==> 0x000068
    exponent = 3
      +128 bias
            ==> 131
            ==> 0x83
  So then we have .db $00,$00,$68,$83.
%=%=%=%=%=%=%=%=%=%=%
1.0 Special Constants
%=%=%=%=%=%=%=%=%=%=%
const_pi:     .db $DB,$0F,$49,$81
const_e:      .db $54,$f8,$2d,$81
const_lg_e:   .db $3b,$AA,$38,$80
const_ln_2:   .db $18,$72,$31,$7f
const_log2:   .db $9b,$20,$1a,$7e
const_lg10:   .db $78,$9a,$54,$81
const_0:      .db $00,$00,$00,$00
const_1:      .db $00,$00,$00,$80
const_inf:    .db $00,$00,$40,$00
const_NegInf: .db $00,$00,$C0,$00
const_NAN:    .db $00,$00,$20,$00
const_10:     .db $00,$00,$20,$83
const_10_inv: .db $CD,$CC,$4C,$7C    ;roughly 0.1
const_pi_inv: .db $83,$F9,$22,$7E
const_e_inv:  .db $B2,$5A,$3C,$7E

%=%=%=%=%=%=%=%=%=%=%
2.0 Single Precision
%=%=%=%=%=%=%=%=%=%=%
  
%=%=%=%=%
2.1 Math
%=%=%=%=%
absSingle
  func: |x| -> z
  mem:  None
addSingle
  func: x+y -> z
  mem:  6 bytes
ameanSingle
  func: (x+y)/2 -> z
  mem:  6 bytes
subSingle
  func: x-y -> z
  mem:  10 bytes
rsubSingle
  func: -x+y -> z
  mem:  10 bytes
invSingle
  func: 1/x -> z
  mem:  5 bytes
divSingle
  func: x/y -> z
  mem:  5 bytes
div255Single
  func: x/255 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div85Single
  func: x/85 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div51Single
  func: x/51 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div17Single
  func: x/17 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div15Single
  func: x/15 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div5Single
  func: x/5 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
div3Single
  func: x/3 -> z
  mem:  None
  Note: This is an optimized, special purpose division.
mulSingle
  func: x*y -> z
  mem:  9 bytes
mul10Single
  func: x*10 -> z
  mem:  None
  Note: This is an optimized, special purpose multiplication.
mulSingle_p375
  func: x*.375 -> z
  mem:  None
  Note: This is an optimized, special purpose multiplication.
        Used in the bgi2 routine
mulSingle_p34375
  func: x*.34375 -> z
  mem:  None
  Note: This is an optimized, special purpose multiplication.
        Used in the bgi routine
mulSingle_p041015625
  func: x*.041015625 -> z
  mem:  None
  Note: This is an optimized, special purpose multiplication.
        Used in the bgi routine
sqrtSingle
  func: sqrt(x) -> z
  mem:  3 bytes
geomeanSingle
  func: sqrt(x*y) -> z
  mem:  9 bytes
cmpSingle
  func: compare x to y, no output
        return z flag if x=y (error is up to the last 2 bits)
        return c flag if x<y
        return nc if x>=y
  mem:  None
negSingle
  func: -x -> z
  mem:  None
lgSingle
  func: lg(x) -> z
  mem:  27 bytes
  note: base 2 logarithm
lnSingle
  func: ln(x) -> z
  mem:  27 bytes
  note: base e logarithm; the natural logarithm
log10Single
  func: log10(x) -> z
  mem:  27 bytes
  note: base 10 logarithm
logSingle
  func: log_y(x) -> z
  mem:  27 bytes
  note: base y logarithm
pow2Single
  func: 2^x -> z
  mem:  18 bytes
expSingle
  func: e^x -> z
  mem:  18 bytes
pow10Single
  func: 10^x -> z
  mem:  18 bytes
powSingle
  func: x^y -> z
  mem:  18 bytes
  note: makes a call to lgSingle, which is why we need 25 bytes
acosSingle
  func: acos(x) -> z
  mem:  31 bytes
acoshSingle
  func: acosh(x) -> z
  mem:  31 bytes
asinSingle
  func: asin(x) -> z
  mem:  31 bytes
asinhSingle
  func: asinh(x) -> z
  mem:  31 bytes
atanSingle
  func: atan(x) -> z
  mem:  31 bytes
atanhSingle
  func: atanh(x) -> z
  mem:  31 bytes
tanSingle:
  func: tan(x) -> z
  mem:  27 bytes
tanhSingle
  func: tanh(x) -> z
  mem:  18 bytes
sinSingle:
  func: sin(x) -> z
  mem:  23 bytes
sinhSingle
  func: sinh(x) -> z
  mem:  18 bytes
cosSingle:
  func: cos(x) -> z
  mem:  23 bytes
coshSingle
  func: cosh(x) -> z
  mem:  18 bytes
randSingle
  func: rand[0,1) -> z
  mem:  None
bg2iSingle
  func: 1/BG(x,y) -> z
  mem:  27 bytes
  Note: This calculates the Borchardt-Gauss mean, to less precision than bgiSingle
        Used to compute ln(x)
bgiSingle
  func: 1/BG(x,y) -> z
  mem:  31 bytes
  Note: This calculates the Borchardt-Gauss mean.
        Used to compute inverse trig and hyperbolic functions.
%=%=%=%=%=%
2.2 Convert
%=%=%=%=%=%
single2str
  func: string(x) -> z
  mem:  19 bytes
single2ti
  func: tifloat(x) -> z
  mem:  19 bytes
str2single
  func: float(str) -> z
  mem:  9 bytes
  note: 'str' is an ASCII string, except $1B is the char for the exponential e, $1A is the negative sign.
ti2single
  NOT YET IMPLEMENTED
single2char
  func: Converts a single-precision float to an 8-bit uint in the A register

%=%=%=%=%=%=%=%=%=%=%=%
3.0 Extended Precision
%=%=%=%=%=%=%=%=%=%=%=%
%=%=%=%=%
3.1 Math
%=%=%=%=%
xadd
  func:  x+y -> z
  mem:   30 bytes
xamean
  func:  (x+y)/2 -> z
  mem:   bytes
xsub
  func:  x-y -> z
  mem:   bytes
xrsub
  func:  y-x -> z
  mem:   bytes
xdiv
  func:  x/y -> z
  mem:   bytes
  
xinv     NOT YET IMPLMENTED
  func:  1/x -> z
  mem:   bytes

xmul
  func:  x*y -> z
  mem:   bytes

xmul10
  func:  x*10 -> z
  mem:   bytes

xsqrt
  func:  sqrt(x) -> z
  mem:   bytes

xgeomean
  func:  sqrt(x*y) -> z
  mem:   bytes
  
xcmp     NOT YET IMPLMENTED
  func: compare x to y, no output
        return z flag if x=y (error is up to the last 2 bits)
        return c flag if x<y
        return nc if x>=y
  mem:  None

xabs     NOT YET IMPLMENTED
  func:  |x| -> z
  mem:   bytes

xneg     NOT YET IMPLMENTED
  func:  -x -> z
  mem:   bytes

xexp     NOT YET IMPLMENTED
  func:  e^x -> z
  mem:   bytes

xpow2    NOT YET IMPLMENTED
  func:  2^x -> z
  mem:   bytes

xpow10   NOT YET IMPLMENTED
  func:  10^x -> z
  mem:   bytes

xpow     NOT YET IMPLMENTED
  func:  x^y -> z
  mem:   bytes

xln
  func:  ln(x) -> z
  mem:   bytes

xlg      NOT YET IMPLMENTED
  func:  log2(x) -> z
  mem:   bytes

xlog10   NOT YET IMPLMENTED
  func:  log10(x) -> z
  mem:   bytes

xlog     NOT YET IMPLMENTED
  func:  log_y(x) -> z
  mem:   bytes

xacos
  func:  acos(x) -> z
  mem:   bytes

xacosh
  func:  acosh(x) -> z
  mem:   bytes

xasin
  func:  asin(x) -> z
  mem:   bytes

xasinh
  func:  asinhx) -> z
  mem:   bytes

xatan
  func:  atan(x) -> z
  mem:   bytes

xatanh
  func:  atanh(x) -> z
  mem:   bytes

xcos     NOT YET IMPLMENTED
  func:  cos(x) -> z
  mem:   bytes

xcosh    NOT YET IMPLMENTED
  func:  cosh(x) -> z
  mem:   bytes

xsin     NOT YET IMPLMENTED
  func:  sin(x) -> z
  mem:   bytes

xsinh    NOT YET IMPLMENTED
  func:  sinh(x) -> z
  mem:   bytes

xtan     NOT YET IMPLMENTED
  func:  tan(x) -> z
  mem:   bytes

xtanh    NOT YET IMPLMENTED
  func:  tanh(x) -> z
  mem:   bytes

xbg
  func:  1/BG(x,y) -> z
  mem:   bytes

xrand
  func:  rand -> z
  mem:   bytes
  Notes: Generates a pseudo-random float on [0,1)
%=%=%=%=%=%=%=%
3.2 Conversion
%=%=%=%=%=%=%=%
xtostr
  func:  str(x) -> z
  mem:   bytes
  Notes: converts the foat to a string

xtoTI    NOT YET IMPLMENTED
  func:  TI(x) -> z
  mem:   bytes
  Notes: converts the float to a TI float

strtox   NOT YET IMPLMENTED
  func:  xfloat(x) -> z
  mem:   bytes
  Notes: converts a string to a float

TItox    NOT YET IMPLMENTED
  func:  xfloat(TI x) -> z
  mem:   bytes
  Notes: converts a TI formatted float to an extended precision float

%=%=%=%=%=%=%=%=%=%
4.0 Other Routines
%=%=%=%=%=%=%=%=%=%
iconstSingle
  `call iconstSingle \ .db x`
  Returns a pointer in HL to a constant
xconst
  `xconst \ .db x`
  Returns a pointer in HL to a constant
pushpop
  `call pushpop`
  This pushes HL,DE,BC, and AF onto the stack
  It then inserts a return address so that when your routine ends, the registers are restored before the final return.
mul16
  BC*DE -> DEHL
mul24
  BDE*CHL -> HLBCDE
mul32
  DEHL*BCIX -> z0_32
mul64
  Multiplies two 64-bit ints.
  xOP1*xOP2 -> xOP3+16
C_Times_BDE
  C*BDE -> CAHL
rand
  HL is a pseudo-random number on [0,65535]
randInit
  Initializes the rand seeds.
sqrtHL
  sqrt(HL)->A
mov4
  moves 4 bytes from HL to DE
mov10
  moves 10 bytes from HL to DE
swapxOP2xOP3
  swaps xOP2 and xOP3
diRestore
  `call diRestore`
  Disables interrupts, but sets up a return call that restores the interrupts when your routine exits.
sqrt32
sqrt64
divide16
div32_16
div32_32
div64_32
div64

%=%=%=%=%=%=%
5.0 Examples
%=%=%=%=%=%=%
  Compute pi/e and output the number on a TI-OS:
    ld hl,const_pi
    ld de,const_e
    ld bc,scrap
    call divSingle
    ld h,b
    ld l,c
    call single2str
    bcall(_PutS)
%=%=%=%=%
6.0 To Do
%=%=%=%=%
ti2single

%=%=%=%=%
7.0 Bugs
%=%=%=%=%
  ameanSingle, technically works, but certain cases will fail.
  geomeanSingle, technically works, but certain cases will fail. Plus there is a better implementation.
  xamean, technically works, but certain cases will fail.
  xgeomean, technically works, but certain cases will fail. Plus there is a better implementation.

%=%=%=%
8.0 Log
%=%=%=%
26 November 2015
    Fixed negSingle. Apparently I made that routine before a standard format.
    Overhauled single2str. Outputs are much prettier, and include rounding.
    Added:
        powSingle, expSingle, exp2Single
        lnSingle, logSingle, log10Single
        tanhSingle, sinhSingle, coshSingle
        randSingle, ameanSingle,exp10
        single2ti, single2char
    sqrtSingle is also hastily added since I'm tired. Literally does x^.5. Accuracy isn't great.
4 December 2015
    Fixed up a major format issue for special numbers ZERO, NAN, INF.
    Finally made a str2single routine. It took longer than expected, so I got hopped up on coffee and boredom on my lunch break and worked it out.
    Now it can be hacked in to the test program to convert OS strings into a number string.
    With that, I found out single2str was horribly bugged on inputs where |x|<.1.
5 December 2015
    Fixed the bug found in single2str.
    Now there might be another issue with str2single with inputs too large.
7 December 2015
    Fixed the sqrtSingle routine to the non-cheating way.
13 December 2015
    Added in sine, cosine, and tangent. The implementation is terrible (Maclaurin Series).
