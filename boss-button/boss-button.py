# Simple demo
# Sits forever listening to serial port
# When you press button, opens website of your choosing.
# Extend this to manny buttons and you'll have a physical web-launcher.

# changed for topical web-page
SITE = "http://hackertyper.net/"

SERIAL_PORT = "COM4"
BAUD_RATE = 9600

import serial
import webbrowser

sp = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout = 5)
sp.flush()

while(1):                     # sit and wait forever
    response = sp.read(1)     # get one byte
    if response == "0":
        print "Got OK Byte. Waiting for button press."
    elif response == "X":
        print "Got Boss Byte! Alarm!"
        webbrowser.open(SITE)
    else:
        print "Got nothing. Still waiting."