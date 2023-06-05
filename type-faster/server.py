import random
from flask import Flask, render_template, request
import json
from datetime import datetime

app = Flask("type-faster", static_url_path='', static_folder='static',)
start_time = None
flag_f = open("flag.txt", "r")
flag = flag_f.read()
flag_f.close()

WORD_COUNT = 3
chars_inp = []
timeses = []

@app.route("/")
def index():
    global char_list
    global chars_inp
    timeses.clear()
    word_file = open("words.txt", "r")
    words = word_file.read().split("\n")
    word_list = [words[random.randint(0, len(words) - 1)] for i in range(WORD_COUNT)]
    char_list = list(" ".join(word_list))
    chars_inp = []
    return render_template("index.html", words=" ".join(word_list))

@app.route("/times", methods=["POST"])
def times():
    
    if "end" in request.data.decode("utf-8"):
        end_time = timeses[-1]
        start_time = timeses[0]
        diff = end_time - start_time
        print(diff)
        if diff <= 8000 and len(chars_inp) == len(char_list):
            return {"flag": flag}
        
        return {"status": "idk"}
    
    elif "event" in request.data.decode("utf-8"):
        event = json.loads(request.data.decode('utf-8'))['event']
        print(event)
        timeses.append(event["when"])
        if event["key"] in "abcdefghijklmnopqrstuvwxyz .,":
            if event["key"] == " " and chars_inp[-1] == " ":
                return {"status": "idk"}
            chars_inp.append(event["key"])
        if event["key"] == "Backspace":
            chars_inp.pop()
        return {"status": "idk"}
    else:
        return {"status": "error"}

@app.errorhandler(404)
@app.errorhandler(500)
@app.route("/<path:path>")
def page_not_found(e=None):
    return render_template('404.html'), 404

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=9023)