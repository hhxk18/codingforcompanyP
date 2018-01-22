from flask import Flask
from flask import request
from flask import render_template

from werkzeug.contrib.cache import SimpleCache
from werkzeug.datastructures import Headers

from json import JSONEncoder
import hashlib

app = Flask(__name__)
cache = SimpleCache()

@app.route('/')
def index():
    m = hashlib.sha256()
    m.update("foo".encode('utf-8'))
    print( m.hexdigest() )
    return '<h1>Foo hash:' + m.hexdigest() + '</h1>'

@app.route('/messages', methods=['POST'])
def encode_message_sha256():
    if request.method == 'POST':
        if 'message' in request.form:
            encodedMessage = request.form['message'].encode('utf-8')
            hexdigest = cache.get( encodedMessage )

            if hexdigest is None:                
                m = hashlib.sha256()
                m.update( encodedMessage )
                timeout = 0; # never expire
                hexdigest = m.hexdigest()
                cache.set( encodedMessage, m.hexdigest(), timeout )
                cache.set( m.hexdigest(), encodedMessage, timeout )

            resp = {
                'digest' : hexdigest
            }
            jresp = JSONEncoder().encode( resp )            
            return jresp
        else:
            return "No attribute message in request!"
        
    return "Only POST method is allowed"

@app.route('/messages/<hexhash>')
def retrieve_message(hexhash=None):
    errorResp = {
        "err_msg" : "Message not found"
    }
    errorHeader = Headers()
    errorHeader.add( 'Content-Type', 'application/json' )
    if hexhash is None:
        return JSONEncoder().encode(errorResp), 404, errorHeader

    message = cache.get( hexhash )
    if message is None:        
        return JSONEncoder().encode(errorResp), 404, errorHeader

    resp = {
        "message" : message.decode('utf-8')
    }
    print( "resp: {}".format( resp ) )
    return JSONEncoder().encode( resp )

if __name__ == '__main__':
    app.run()
