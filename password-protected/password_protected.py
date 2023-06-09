import re

banner = ''' ______   ______     ______     ______     __     __     ______     ______     _____        __  __    
/\  == \ /\  __ \   /\  ___\   /\  ___\   /\ \  _ \ \   /\  __ \   /\  == \   /\  __-.     /\_\_\_\   
\ \  _-/ \ \  __ \  \ \___  \  \ \___  \  \ \ \/ ".\ \  \ \ \/\ \  \ \  __<   \ \ \/\ \    \/_/\_\/_  
 \ \_\    \ \_\ \_\  \/\_____\  \/\_____\  \ \__/".~\_\  \ \_____\  \ \_\ \_\  \ \____-      /\_\/\_\ 
  \/_/     \/_/\/_/   \/_____/   \/_____/   \/_/   \/_/   \/_____/   \/_/ /_/   \/____/      \/_/\/_/ 
'''

def checkValidPassword(hashType, salt, hash, password):
  
  #Implementation not shown
  #If it is the requested user, with the valid password, it will print flag

  pass

print(banner)
print("Welcome to the PasswordX interface\n")

accountName = input("Please enter the username associated with your account: ")

passwd = open("etc/passwd")
shadow = open("etc/shadow").read()
pattern = re.compile("\$\d\$.+\$.+")

successful = False

for line in passwd:
  if (line.split(":")[0] in accountName):
    shadowTextStartIndex = shadow.index(line.split(":")[0])
    hashIndex = shadowTextStartIndex+len(accountName)+1

    hash = shadow[hashIndex:].split(":")[0]
    if not re.match(pattern, hash):
      raise ValueError(f"String {hash} does not match required regex \$\d\$.+\$.+")
    
    _,hashType,salt,hash = hash.split("$")
    hashType = int(hashType)

    password = input("Please enter the password associated with your account: ")

    checkValidPassword(hashType,salt,hash,password)
  
print("Please come again!")