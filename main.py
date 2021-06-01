#web服务器
#建立数据库之后第二个启动

import sqlite3
from flask import Flask, request, render_template, jsonify





app = Flask(__name__)

#连接数据库
def get_db():
    db = sqlite3.connect('mydb.db')
    db.row_factory = sqlite3.Row
    return db

#取数据
def query_db(query, args=(), one=False):
    db = get_db()
    cur = db.execute(query, args)
    db.commit()
    rv = cur.fetchall()
    db.close()
    return (rv[0] if rv else None) if one else rv

#首页html
@app.route("/", methods=["GET"])
def index():
    return render_template("index.html")

#ajax更新数据
@app.route("/weather", methods=["GET", "POST"])
def weather():
    if request.method == "GET":
        res = query_db("SELECT * FROM weather WHERE id <= 6")  # 第一次只返回6个数据
    elif request.method == "POST":
        res = query_db("SELECT * FROM weather WHERE id = (?)", args=(int(request.form['id']) + 1,))  # 以后每次返回1个数据

    return jsonify(id=[x[0] for x in res],
                   sensor1=[x[1] for x in res],
                   sensor2=[x[2] for x in res],
                   sensor3=[x[3] for x in res],
                   status=[x[4] for x in res],
                   xarray=[x[5] for x in res],
                   yarray=[x[6] for x in res],
                   x1array=[x[7] for x in res],
                   y1array=[x[8] for x in res])  # 返回json格式

if __name__ == "__main__":
    app.run(debug=True)