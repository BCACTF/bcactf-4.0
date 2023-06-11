import random
from flask import Flask, render_template, request, session
from flask_session import Session
import json

app = Flask("type-faster", static_url_path='', static_folder='static',)
start_time = None
flag_f = open("flag.txt", "r")
flag = flag_f.read()
flag_f.close()
app.secret_key = 'bcactfhasaverysecurestringofsessiontokenkeyshahahaha2w9un2rind3h4db'

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

WORD_COUNT = 70

@app.route("/")
def index():
    session["timeses"] = session["timeses"] if "timeses" in session.keys() else []
    session["chars_inp"] = session["chars_inp"] if "chars_inp" in session.keys() else []
    word_file = open("words.txt", "r")
    words = word_file.read().split("\n")
    word_list = [words[random.randint(0, len(words) - 1)] for i in range(WORD_COUNT)]
    session["char_list"] = list(" ".join(word_list))
    
    return render_template("index.html", words=" ".join(word_list))

@app.route("/times", methods=["POST"])
def times():
    if "end" in request.data.decode("utf-8"):
        if len(session["timeses"]) < 2:
            return {"status": "Failed"}
        start_time = session["timeses"][0]
        end_time = session["timeses"][-1]
        diff = end_time - start_time
        if diff <= 8000 and len(session["chars_inp"]) == len(session["char_list"]):
            return {"flag": flag}
        print(end_time, start_time, diff)
        print(len(session["chars_inp"]), len(session["char_list"]))
        return {"status": "ok"}
    
    elif "event" in request.data.decode("utf-8"):
        event = json.loads(request.data.decode('utf-8'))['event']
        
        chars_inp = session["chars_inp"]
        print(session["timeses"])
        session["timeses"].append(event["when"])
        print(session["timeses"])
        if event["key"] in "abcdefghijklmnopqrstuvwxyz .,":
            if event["key"] == " " and len(chars_inp) > 0 and chars_inp[-1] == " ":
                return {"status": "ok"}
            session["chars_inp"].append(event["key"])
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