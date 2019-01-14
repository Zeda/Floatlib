#macro args_ss(src1,src2)
    ld hl,src1
#if src1==src2
    ld d,h
    ld e,l
#else
    ld de,src2
#endif
#endmacro
#macro args_sd(src,dest)
    ld hl,src
#if src==dest
    ld b,h
    ld c,l
#else
    ld bc,dest
#endif
#endmacro
#macro args_ssd(src1,src2,dest)
    ld hl,src1
#if src1==src2
    ld d,h
    ld e,l
#else
    ld de,src2
#endif
#if (dest==src1)|(dest==src2)
#if dest==src1
    ld b,h
    ld c,l
#else
    ld b,d
    ld c,e
#endif
#else
.echo "works"
    ld bc,dest
#endif
#endmacro

#define fadd(src1,src2,dest)  args_ssd(src1,src2,dest) \ call addSingle
#define fsub(src1,src2,dest)  args_ssd(src1,src2,dest) \ call subSingle
#define frsub(src1,src2,dest) args_ssd(src1,src2,dest) \ call rsubSingle
#define fmul(src1,src2,dest)  args_ssd(src1,src2,dest) \ call mulSingle
#define fsqr(src,dest)        args_ssd(src,src,dest)   \ call mulSingle
#define fcmp(src1,src2)       args_ss(src1,src2)       \ call cmpSingle
#define fmov(src,dest)        args_ss(src,dest)        \ ldi \ ldi \ ldi \ ldi
#define ffmov(src,dest)       ld hl,(src) \ ld (dest),hl \ ld hl,(src+2) \ ld (dest+2),hl
scrap   = 8000h
vars    = scrap+29  ;After this point there is freely available RAM
curKey  = 80F6h
keyCount= 80F7h
seed1   = 80F8h
seed2   = 80FCh
;flags       =89F0h
mathflags   =21h
ext         = 0

iconstSingle = 4024h
absSingle   = 4027h
addSingle   = 402Ah
subSingle   = 402Dh
rsubSingle  = 4030h
ameanSingle = 4033h
cmpSingle   = 4036h
divSingle   = 4039h
invSingle   = 403Ch
expSingle   = 403Fh
powSingle   = 4042h
exp10Single = 4045h
exp2Single  = 4048h
geomeanSingle=404Bh
sinhSingle  = 404Eh
coshSingle  = 4051h
tanhSingle  = 4054h
logSingle   = 4057h
lnSingle    = 405Ah
log10Single = 405Dh
lgSingle    = 4060h
mulSingle   = 4063h
mul10Single = 4066h
mul24       = 4069h
C_times_BDE = 406Ch
negSingle   = 406Fh
randSingle  = 4072h
seedRand    = 4075h
rand        = 4078h
single2char = 407Bh
single2str  = 407Eh
single2TI   = 4081h
sqrtSingle  = 4084h
sqrt        = 4087h
str2single  = 408Ah
sinSingle   = 408Dh
cosSingle   = 4090h
tanSingle   = 4093h
tistrToSingle = 4096h     ;converts Ans as a string 

;ld a,# \ call _constants
;This loads a pointer to a constant into HL, destroys A
_pi     = 0
_e      = 1
_pi_div_ln2=2
_lg_e   = 3
_ln_2   = 4
_log2   = 5
_lg10   = 6
_0      = 7
_1      = 8
_inf    = 9
_NegInf = 10
_NAN    = 11
_10     = 12
_10_inv = 13
_pi_inv = 14
_e_inv  = 15
