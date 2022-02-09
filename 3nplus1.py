

print("Enter series pair")
i=int(input("Enter first integer"))
j=int(input("Enter second integer"))

count = 0
cnt = 0

for x in range(i,j+1) :
        while x>1:
                if x % 2 == 0 :
                        x = x // 2
                        
                else :
                        x = (3*x) + 1
                      
                count = count +1
        count = count + 1

        if cnt < count :
                        cnt = count
        count = 0
print(i)
print(j)
print(cnt)
