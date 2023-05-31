import random
from flask import Flask, render_template, request
import json
from datetime import datetime

app = Flask("type-faster", static_url_path='', static_folder='static',)
start_time = None
flag_f = open("flag.txt", "r")
flag = flag_f.read()
flag_f.close()

WORD_COUNT = 70

@app.route("/")
def index():
    word_file = open("words.txt", "r")
    words = word_file.read().split("\n")
    word_list = [words[random.randint(0, len(words) - 1)] for i in range(WORD_COUNT)]
    return render_template("index.html", words=" ".join(word_list))

@app.route("/times", methods=["POST"])
def times():
    global start_time
    if "start_time" in request.data.decode("utf-8"):
        start_time = int(json.loads(request.data.decode("utf-8"))["start_time"])
        return {"status": "ok"}
    elif "end_time" in request.data.decode("utf-8"):
        end_time = int(json.loads(request.data.decode("utf-8"))["end_time"])
        diff = end_time - start_time
        if diff <= 8000:
            return {"flag": flag}
        
        return {"status": diff}
    elif "event" in request.data.decode("utf-8"):
        event = json.loads(request.data.decode('utf-8'))['event']
        print(event)
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