from flask import Flask, render_template, request, url_for
from werkzeug.utils import redirect
import os
import json

app = Flask(__name__)

@app.route('/',methods = ['POST', 'GET'])
def base():
   return render_template('led.html')

@app.route("/result",methods = ['POST','GET'])
def _led():
    state = request.form["Onoff"]
    if (state == "on") or (state == "off"):
        s = {
            "led" : state
        }
        fname = os.path.join(app.static_folder, "sample.json")
        with open(fname, "w") as outfile:
            json.dump(s, outfile)
        return "LED " + state
    elif state == "on?":
        return redirect(url_for('.readJSON'))
    else:
        return "Please enter one of the three values: on, off, on? "

@app.route("/read")
def readJSON():
    fname = os.path.join(app.static_folder, "sample.json")
    with open(fname, "r") as openfile:
        json_obj = json.load(openfile)
    return json_obj["led"]

if __name__ == "__main__":
    app.run(host='0.0.0.0', port= 5000)
