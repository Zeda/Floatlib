;Generated floatlib.inc
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

#define addx(src1,src2,dest)  args_ssd(src1,src2,dest) \ call xadd
#define subx(src1,src2,dest)  args_ssd(src1,src2,dest) \ call xsub
#define rsubx(src1,src2,dest) args_ssd(src1,src2,dest) \ call xrsub
#define mulx(src1,src2,dest)  args_ssd(src1,src2,dest) \ call xmul
#define sqrx(src,dest)        args_ssd(src,src,dest)   \ call xmul
#define cmpx(src1,src2)       args_ss(src1,src2)       \ call xcmp
#define movx(src,dest)        args_ss(src,dest)        \ call mov10
#define fmovx(src,dest)       ld hl,(src) \ ld (dest),hl \ ld hl,(src+2) \ ld (dest+2),hl \ ld hl,(src+4) \ ld (dest+4),hl \ ld hl,(src+6) \ ld (dest+6),hl \ ld hl,(src+8) \ ld (dest+8),hl

#define fadd(src1,src2,dest)  args_ssd(src1,src2,dest) \ call addSingle
#define fsub(src1,src2,dest)  args_ssd(src1,src2,dest) \ call subSingle
#define frsub(src1,src2,dest) args_ssd(src1,src2,dest) \ call rsubSingle
#define fmul(src1,src2,dest)  args_ssd(src1,src2,dest) \ call mulSingle
#define fsqr(src,dest)        args_ssd(src,src,dest)   \ call mulSingle
#define fcmp(src1,src2)       args_ss(src1,src2)       \ call cmpSingle
#define fmov(src,dest)        args_ss(src,dest)        \ call mov4
#define ffmov(src,dest)       ld hl,(src) \ ld (dest),hl \ ld hl,(src+2) \ ld (dest+2),hl

scrap   = 8000h
vars    = scrap+29  ;After this point there is freely available RAM
seed1   = 80F8h
seed2   = 80FCh

;constant IDs for single precision
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

;Library Calls
iconstSingle        = $4024
pushpop             = $4027
addSingle           = $402A
ameanSingle         = $402D
subSingle           = $4030
rsubSingle          = $4033
divSingle           = $4036
invSingle           = $4039
mulSingle           = $403C
mul10Single         = $403F
sqrtSingle          = $4042
geomeanSingle       = $4045
cmpSingle           = $4048
absSingle           = $404B
negSingle           = $404E
expSingle           = $4051
pow2Single          = $4054
pow10Single         = $4057
powSingle           = $405A
lnSingle            = $405D
lgSingle            = $4060
log10Single         = $4063
logSingle           = $4066
acosSingle          = $4069
acoshSingle         = $406C
asinSingle          = $406F
asinhSingle         = $4072
atanSingle          = $4075
atanhSingle         = $4078
cosSingle           = $407B
coshSingle          = $407E
sinSingle           = $4081
sinhSingle          = $4084
tanSingle           = $4087
tanhSingle          = $408A
bg2iSingle          = $408D
bgiSingle           = $4090
div255Single        = $4093
div85Single         = $4096
div51Single         = $4099
div17Single         = $409C
div15Single         = $409F
div5Single          = $40A2
div3Single          = $40A5
mulSingle_p375      = $40A8
mulSingle_p34375    = $40AB
mulSingle_p041015625= $40AE
randSingle          = $40B1
single2str          = $40B4
single2TI           = $40B7
str2single          = $40BA
ti2single           = $40BD
single2char         = $40C0
xconst              = $40C3
xadd                = $40C6
xamean              = $40C9
xsub                = $40CC
xrsub               = $40CF
xdiv                = $40D2
xinv                = $40D5
xmul                = $40D8
xmul10              = $40DB
xsqrt               = $40DE
xgeomean            = $40E1
xcmp                = $40E4
xabs                = $40E7
xneg                = $40EA
xexp                = $40ED
xpow2               = $40F0
xpow10              = $40F3
xpow                = $40F6
xln                 = $40F9
xlg                 = $40FC
xlog10              = $40FF
xlog                = $4102
xacos               = $4105
xacosh              = $4108
xasin               = $410B
xasinh              = $410E
xatan               = $4111
xatanh              = $4114
xcos                = $4117
xcosh               = $411A
xsin                = $411D
xsinh               = $4120
xtan                = $4123
xtanh               = $4126
xbg                 = $4129
xrand               = $412C
xtostr              = $412F
xtoTI               = $4132
strtox              = $4135
TItox               = $4138
mul16               = $413B
mul24               = $413E
mul32               = $4141
mul64               = $4144
C_Times_BDE         = $4147
rand                = $414A
randInit            = $414D
sqrtHL              = $4150
sqrt32              = $4153
sqrt64              = $4156
divide16            = $4159
div32_16            = $415C
div32_32            = $415F
div64_32            = $4162
div64               = $4165
mov4                = $4168
mov10               = $416B
swapxOP2xOP3        = $416E
diRestore           = $4171
