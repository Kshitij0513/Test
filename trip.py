nop=0

print("enter total no of people")
nop=int(input())
ls=[]
print("enter the money spent by each one of them")
for i in range(0,nop):
    
    t=float(input())
    ls.append(t)
total=exp=0
for i in ls:
    total=total+i
ph=total/nop
for i in ls:
    if i<ph:
        exp=ph-i+exp
        
print("money needed to be exchanged to equalize the students costs")
print(exp)
