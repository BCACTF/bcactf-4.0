from flask import Flask, render_template, redirect, url_for, send_from_directory

app = Flask('app')
invalid_file_types = ['py', 'php', 'java', 'md', 'sh']

@app.route('/<path:path>')
def expose(path):
    if path.split('.')[-1] in invalid_file_types:
        return redirect('/403')
    try:
        return send_from_directory(directory='./', path=path)
    except Exception as e:
        print(f'errorr: {e}, path: {path} ::')
        return redirect(url_for('not_found'))
    
@app.route('/403')
def no():
    return render_template('403.html')

@app.route('/404')
def not_found():
    return render_template('404.html')

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)