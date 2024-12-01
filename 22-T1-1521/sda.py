import math
xfir=3
xsec=0
xthi=2
for i in range(58):
    print(xfir,xsec,xthi)
    xfou=xthi-5*xsec+xfir
    print(xfou)
    xfir=xsec
    xsec=xthi
    xthi=xfou

print(xsec)