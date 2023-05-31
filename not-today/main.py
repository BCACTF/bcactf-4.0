import datetime
from flask import Flask, request, jsonify, render_template

app = Flask("not-today")

@app.route("/", methods=["GET"])
def index():
    today = datetime.datetime.now().strftime("%A, %B %d")
    return render_template("index.html", context={"today":today, "flag": ""})

@app.route("/api", methods=["POST"])
def api():
    date = request.json["date"]
    flag = ''
    if "Wed Jun 07 2023 06:09:42 GMT+∀ (BCA Special Time)" in date:
        flag = open("flag.txt", "r").read()
    else:
        flag = "It is not time to be distributing flags 😱"
    return jsonify({"flag": flag})


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=9019)