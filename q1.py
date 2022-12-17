
def fact(n):
    ans = 1

    while(n):
        ans = ans*n
        n -= 1
    

    return ans

n = int(input())

if n <= 100:
    print("invalid input")
else:
    print(fact(n))
