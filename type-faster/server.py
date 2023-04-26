from flask import Flask, render_template, request, redirect, url_for, session

app = Flask("type-faster")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/times", methods=["POST"])
def times():
    if request.headers["Content-Type"] == "text/event-stream":
        with open("times.txt", "a") as f:
            pass
    # read the file

    # write the file to the response
    # add a route
    #check the headers for the event type
    # check the event type
    # write the 'start_time' header to a new file with the name by the user id
    #open the file with the user id

    # check time difference to be less than 5 seconds

    # send the flag if it is less than 5 seconds