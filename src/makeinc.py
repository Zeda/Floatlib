ptr=0x4024      #start of the jump table

#read the jump table
f=open("jumptable.z80",'r')
s=f.read().split('\n')
f.close()

#begin parsing
t=''';Generated floatlib.inc
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
'''
for i in s:
    if i.strip().startswith("jp "):
        i=i.split(";")
        r=i[0].strip()[3:].strip()     #remove comments and surrounding white space. Not gonna bother with error checking, it's your/my own fault if something goes wrong.
        t+=r+" "*(20-len(r))+"= $"+hex(ptr)[2:].upper()
        if len(i)>1:
            for j in i[1:]:
                t+="  ;"+j
        ptr+=3
        t+='\n'
f=open("floatlib.inc",'w')
f.write(t)
f.close()
