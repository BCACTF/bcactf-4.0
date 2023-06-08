
f2 = open("FEN.txt","r")
flag = ""

for line in f2:
    count = 0;
    for char in line:
        if char.upper()=='P':
            count+=1
        if char.upper()=='N':
            count+=3
        if char.upper()=='B':
            count+=3
        if char.upper()=='R':
            count+=5
        if char.upper()=='Q':
            count+=9
    flag+=chr(count)
print(flag)