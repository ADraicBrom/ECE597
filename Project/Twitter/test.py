import pycurl, json

STREAM_URL = "http://chirpstream.twitter.com/2b/user.json"

USER = "segphault"
PASS = "XXXXXXXXX"

def on_receive(data):
  print data

conn = pycurl.Curl()
conn.setopt(pycurl.USERPWD, "%s:%s" % (USER, PASS))
conn.setopt(pycurl.URL, STREAM_URL)
conn.setopt(pycurl.WRITEFUNCTION, on_receive)
conn.perform()
