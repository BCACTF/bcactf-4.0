import random
from flask import Flask, render_template, request, session
import json
from datetime import datetime

app = Flask("type-faster", static_url_path='', static_folder='static',)
start_time = None
flag_f = open("flag.txt", "r")
flag = flag_f.read()
flag_f.close()
app.secret_key = 'bcactfhasaverysecurestringofsessiontokenkeyshahahaha2w9un2rind3h4db'

WORD_COUNT = 3

@app.route("/")
def index():
    if not session.get("timeses"):
        print("Hello")
        session["timeses"] = [100000]
        session["chars_inp"] = []
        word_file = open("words.txt", "r")
        words = word_file.read().split("\n")
        word_list = [words[random.randint(0, len(words) - 1)] for i in range(WORD_COUNT)]
        session["char_list"] = list(" ".join(word_list))
    
    return render_template("index.html", words=" ".join(word_list))

@app.route("/times", methods=["POST"])
def times():
    if "end" in request.data.decode("utf-8"):
        if session["timeses"] == []:
            # print("ERROR")
            # print(session)
            return {"status": "Failed"}
        start_time = session["timeses"][0]
        end_time = session["timeses"][-1]
        diff = end_time - start_time
        # print(diff)
        if diff <= 8000 and len(session["chars_inp"]) == len(session["char_list"]):
            return {"flag": flag}
        
        return {"status": "ok"}
    
    elif "event" in request.data.decode("utf-8"):
        event = json.loads(request.data.decode('utf-8'))['event']
        # print(event)
        chars_inp = session["chars_inp"]
        session["timeses"].append(event["when"])
        print(f"TimeStamps: {','.join([str(i) for i in session['timeses']])}")
        if event["key"] in "abcdefghijklmnopqrstuvwxyz .,":
            if event["key"] == " " and chars_inp[-1] == " ":
                return {"status": "ok"}
            session["chars_inp"].append(event["key"])
            # print(session["chars_inp"])
        if event["key"] == "Backspace":
            session["chars_inp"].pop()
        return {"status": "ok"}
    else:
        return {"status": "error"}

@app.errorhandler(404)
@app.errorhandler(500)
@app.route("/<path:path>")
def page_not_found(e=None):
    return render_template('404.html'), 404

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=9023)