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

%=%=%=%=%=%=%
2.0 Routines
%=%=%=%=%=%=%

%=%=%=%=%
2.1 Math
%=%=%=%=%
absSingle
  func: |x| -> z
  mem:  None
addSingle
  func: x+y -> z
  mem:  6 bytes
  Note: special cases not done
ameanSingle
  func: (x+y)/2 -> z
  mem:  6 bytes
  Note: special cases not done
subSingle
  func: x-y -> z
  mem:  10 bytes
  Note: special cases not done
rsubSingle
  func: -x+y -> z
  mem:  10 bytes
  Note: special cases not done
invSingle
  func: 1/x -> z
  mem:  5 bytes
divSingle
  func: x/y -> z
  mem:  5 bytes
mulSingle
  func: x*y -> z
  mem:  9 bytes
sqrtSingle
  func: sqrt(x) -> z
  mem:  None
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
  mem:  25 bytes
  note: base 2 logarithm
lnSingle
  func: ln(x) -> z
  mem:  25 bytes
  note: base e logarithm; the natural logarithm
log10Single
  func: log10(x) -> z
  mem:  25 bytes
  note: base 10 logarithm
logSingle
  func: log_y(x) -> z
  mem:  29 bytes
  note: base y logarithm
exp2Single
  func: 2^x -> z
  mem:  11 bytes
expSingle
  func: e^x -> z
  mem:  11 bytes
exp10Single
  func: 10^x -> z
  mem:  11 bytes
powSingle
  func: x^y -> z
  mem:  25 bytes
  note: makes a call to lgSingle, which is why we need 25 bytes
tanhSingle
  func: tanh(x) -> z
  mem:  13 bytes
sinhSingle
  func: sinh(x) -> z
  mem:  17 bytes
coshSingle
  func: cosh(x) -> z
  mem:  17 bytes
randSingle
  func: rand[0,1) -> z
  mem:  None
sinSingle:
  func: sin(x) -> z
  mem:  26 bytes
cosSingle:
  func: cos(x) -> z
  mem:  26 bytes
tanSingle:
  func: tan(x) -> z
  mem:  26 bytes
%=%=%=%=%=%
2.2 Convert
%=%=%=%=%=%
single2string
  func: string(x) -> z
  mem:  20 bytes
single2ti
  func: tifloat(x) -> z
  mem:  20 bytes
str2single
  func: float(str) -> z
  mem:  29 bytes
  note: 'str' is an ASCII string, except $1B is the char for the exponential e, $1A is the negative sign.
%=%=%=%=%=%=%
3.0 Examples
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
%=%=%=%
4.0 Log
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
%=%=%=%=%
5.0 To Do
%=%=%=%=%
ti2single

%=%=%=%=%
6.0 Bugs
%=%=%=%=%
  str2single does not yet evaluate the engineering E and it's following exponent.
  single2str crashes on certain inputs.
  ameanSingle, technically works, but certain cases will fail.
  geomeanSingle, technically works, but certain cases will fail. Plus there is a better implementation.
  divSingle was not properly detecting underflow/overflow so the code is currently removed.
  addSingle seems to be failing for largely differing numbers. ex (55.7^2)+1
