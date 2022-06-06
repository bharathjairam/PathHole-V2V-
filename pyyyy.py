# Importing Libraries
import geocoder
import serial
import time

json_data = "1,99.2,777.9"
arduino = serial.Serial(port='COM16', baudrate=9600, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(1)
    data = arduino.readline()
    return data

while True:
    g = geocoder.ip('me')
    value = write_read("1"+str(g.latlng))
    print(value) # printing the value
    time.sleep(2)
