import itertools
arr=input().split()
s=' +-*'
res=set()
for ind in itertools.permutations("0123",4):
    a=arr[int(ind[0])]
    b=arr[int(ind[1])]
    c=arr[int(ind[2])]
    d=arr[int(ind[3])]
    for i in range(4):
        for j in range(4):
            for k in range(4):
                if i+j+k==0:
                    continue;
                ex=a+(s[i] if i>0 else '')+b+(s[j] if j>0 else '')+c+(s[k] if k>0 else '')+d
                v=eval(ex)
                if v>=0:
                    res.add(v)
print(len(res))
