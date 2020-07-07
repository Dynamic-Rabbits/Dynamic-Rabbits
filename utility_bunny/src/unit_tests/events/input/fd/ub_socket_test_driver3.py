import socket
import sys
import thread
import subprocess
import time
import os

drrun = sys.argv[1]
client = sys.argv[2]
app = sys.argv[3]

if len(sys.argv) == 5:
  app_params = sys.argv[4]
else:
  app_params = ""

def run_test(drrun, client, app, app_params):

  print("GONNA RUN!")
 
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  print 'Socket created'
 
  try:
    s.bind(('', 7717))
  except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
  print 'Socket bind complete'
 
  s.listen(10)
  
  conn, addr = s.accept()
  print 'Connected with ' + addr[0] + ':' + str(addr[1])

  conn.send("HELLO")
  time.sleep(1)
  conn.send("END")
  
  s.close()
  time.sleep(1)
  print("DONE RUNNING!")
  
thread.start_new_thread(run_test, (drrun, client, app, app_params))

time.sleep(1)

returncode = subprocess.call(drrun + " -max_bb_instrs 5 -syntax_intel -c " + client + " -- " + app + " " + app_params, shell=True)
               
print("EXITING")
os._exit(returncode)
