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
 
  print("GONNA RUN!!!!!!!!!!!!!!!!!!")
 
  returncode = subprocess.call(drrun + " -max_bb_instrs 5 -syntax_intel -c " + client + " -- " + app + " " + app_params, shell=True)
 
  print("EXITING!!!!!!!!!!!!!!!!!!!!!")
  os._exit(returncode)
   
# Create two threads as follows
thread.start_new_thread(run_test, (drrun, client, app, app_params))

time.sleep(4)

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 7717))
client_socket.send("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
client_socket.close()
