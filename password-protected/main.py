import re

banner = ''' ______   ______     ______     ______     __     __     ______     ______     _____        __  __    
/\  == \ /\  __ \   /\  ___\   /\  ___\   /\ \  _ \ \   /\  __ \   /\  == \   /\  __-.     /\_\_\_\   
\ \  _-/ \ \  __ \  \ \___  \  \ \___  \  \ \ \/ ".\ \  \ \ \/\ \  \ \  __<   \ \ \/\ \    \/_/\_\/_  
 \ \_\    \ \_\ \_\  \/\_____\  \/\_____\  \ \__/".~\_\  \ \_____\  \ \_\ \_\  \ \____-      /\_\/\_\ 
  \/_/     \/_/\/_/   \/_____/   \/_____/   \/_/   \/_/   \/_____/   \/_/ /_/   \/____/      \/_/\/_/ 
'''

def checkValidPassWord(hashType, salt, hash, password):
  
  accounts = {"root":"ona092406",
              "arvgar":"pansoncitapansoncita",
              "madale":"oyoTbpk101236",
              "wilsyl":"wonkawilly",
              "linalp":"tarpon4499",
              "rhyrob":"559123abc",
              "orazac":"rebeyroly4ever",
              "jonwil":"santynkellybffs",
              "deihaz":"regina11",
              "dorrow":"20201purple",
              "clacar":"iloveyou",
              "chaana":"48151623424223161584",
              "flomar":"666248389guaman",
              "shaart":"lovepink2",
              "waltru":"cristininha",
              "catcan":"teamoalessandra",
              }

  if (accountName.startswith("root")):
    actualAccountName = "root"
  else:
    actualAccountName = accountName[:6]
  
  if (accounts[actualAccountName] == password):
    if actualAccountName == "jonwil":
      print("bcactf{Passw0Rd_Pr0ffessional}")
    else:
      print("Incorrect Account, please log into Jon Wilkie's account")
  else:
    print("Incorrect Password")

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
      print(f"String {hash} does not match required regex \$\d\$.+\$.+")
      exit()
    
    _,hashType,salt,hash = hash.split("$")
    hashType = int(hashType)

    password = input("Please enter the password associated with your account: ")

    checkValidPassWord(hashType,salt,hash,password)      

print("Please come again!")