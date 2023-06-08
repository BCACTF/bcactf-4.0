import random;
f2 = open("FEN.txt","w")
flag = "bcactf{b15h0ps_4r3n7_kn16ht5_34j21nd92}"

def boardToFEN(board):
    #print(board)
    #input()
    ret =""
    
    for i in range(8):
        count = 0
        for j in range(8):
            if board[i][j]==0:
                count+=1;
            else:
                if count>0:
                    ret+=str(count)
                
                options = ""
                if board[i][j]==1:
                    options = "pP"
                if board[i][j]==3:
                    options = "bBnN"
                if board[i][j]==5:
                    options = "rR"
                if board[i][j]==9:
                    options = "qQ"
                char = options[random.randint(0,len(options)-1)]

                #print(char)
                ret += char
                count = 0
        if count>0:
                #print(count)
                ret+=str(count)
        if (i!=7):
            ret+='/'

    return ret
    


for char in flag:
    num = ord(char)
    print(num)
    board = [[0] * 8 for _ in range(8)]

    used = 0
    while used<num:
        r = random.randint(1,15)
        p =0
        if (r<=8):
            p = 1
        elif (r<=12):
            p = 3
        elif (r<=14):
            p=5
        else:
            p=9
        if (p+used>num):
            continue
        x = random.randint(0,7)
        y = random.randint(0,7)
        if (board[x][y]<p):
            used+=p
            used-=board[x][y]
            board[x][y]=p
        
    boardFEN = boardToFEN(board);
    print(boardFEN)
    f2.write(boardFEN+"\n")
    
    #break
