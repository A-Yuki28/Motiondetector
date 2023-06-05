import requests
import serial
import time
 
ser = serial.Serial('COM3', 9600) # ここのポート番号を変更
ser.readline()
while True:
   val_arduino = ser.readline()
  
   str = val_arduino.decode()
   print(val_arduino)
   strs = str.split(',')
   
   eventid = "line_event"
   key = "cQy1b4pnf-vFcWQfWsayTG5AzEkayGhPVBnnQX7mypS" # IFTTTキー
   payload = {"value1": strs[0], "value2": strs[1], "value3": strs[2] }
   url = "https://maker.ifttt.com/trigger/" + eventid + "/with/key/" + key
   response = requests.post(url, data=payload)
ser.close()