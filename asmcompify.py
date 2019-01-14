inc="docs/floatlib.inc"
f=open(inc,'r+')
data=f.readlines()
f.close()
d=[]
for i in data:
    i=i.split(';')[0]
    i=i.split('=')[0]
    i=i.strip()
    if len(i)!=0:
        d+=[': .db "'+i.upper()+',0" \ .dw '+i+'\n']
d=sorted(d)
s='.dw '+str(len(d))+'\n'
for i in range(len(d)):
    s+='.dw equ_'+str(i)+'\n'
    d[i]='equ_'+str(i)+d[i]
d=['#include "'+inc+'"\n','#define equb(x,y) .db 8,x,9 \ .db y\n','#define equ(x,y)  .db 6,x,7 \ .dw y\n',s]+d
f=open('asmcompequ.z80','w+')
f.writelines(d)
f.close()
