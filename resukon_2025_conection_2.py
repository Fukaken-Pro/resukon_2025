import socket
import serial
import time
from concurrent.futures import ThreadPoolExecutor
socket.setdefaulttimeout(1.0)
# from onsei_ras import audioin

# def audio_send(ip):
#   rec = audioin()
#   rec.record()
#   rec.rec_send(ip)

class conection:
  def __init__(self):
    
    self.data_return = []
    self.ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    self.sv = socket.socket(socket.AF_INET)
    self.port = 36133
    self.back_port = 36132
    self.contime = []

  def serialtusin(self):
    kaisu=0
    msg = str(self.data_return[-1]) + "\n"
    self.ser.write(msg.encode('utf-8'))
    while self.ser.in_waiting > 0:
      print("A")
      if(kaisu>=100):
          break
      else:
          kaisu+=1
    if(kaisu<=100):
        line = self.ser.readline().decode('utf-8').rstrip()
        print(line)

  def responseToCommand(self, client, addr):
    start = time.time()
    # 処理：コンソールにエコーする
    data = client.recv(1024)
    comand = data.decode("utf-8")
    # クライアントに返答
    res = socket.socket(socket.AF_INET)
    res.connect((addr[0], self.back_port))
    res.send("Thank you!".encode("utf-8"))
    client.close()
    res.close()
    end = time.time()
    print(comand)
    return [comand, end - start]

  def tunagu(self):
    client, addr = self.sv.accept()
    self.responseToCommand(client,addr)
    return client

  def backlog(self):
    datacheck=lambda datacount:datacount>0
    if(datacheck(len(self.data_return))):
        with ThreadPoolExecutor(max_workers=1) as executor:
          setuzoku = executor.submit(self.tunagu)
          while (datacheck(len(self.data_return))):
            self.serialtusin()
            self.data_return.pop(-1)
            time.sleep(self.contime[-1])
            self.contime.pop(-1)
            try:
                client = setuzoku.result(timeout=1)
                client.close()
            except TimeoutError:
                continue
            except:
                print("なんかエラー")
            else:
                break  
            break


def conconection():
  cnc = conection()
  cnc.ser.flush()
  cnc.sv.bind(("10.133.6.156", cnc.port))
  cnc.sv.listen()
  z = 0
  while True:
    try:
            client, addr = cnc.sv.accept()
      # 別スレッドでクライアントに返答
                
            cnc.data_return.append(cnc.responseToCommand(client, addr))
            if(not type(cnc.data_return[-1][0])==int):
                cnc.contime.append(cnc.data_return[-1].pop(-1))
                cnc.data_return[-1]=cnc.data_return[-1][0]
                #print(cnc.data_return)
                cnc.serialtusin()
            else:
                cnc.data_return.pop()

            if (not cnc.data_return[-1][:1] == "0" and not cnc.data_return[-1][:1] == "1"):
              cnc.data_return.pop(-1)
            elif (len(cnc.data_return) > 10):
              cnc.data_return.pop(0)

    except TimeoutError:
         pass
#           print("timeout")
#           cnc.backlog()



