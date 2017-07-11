import serial

def readValue(serialPort):
    return(ord(serialPort.read(1)))

def plotValue(value):
    # Displays the value on a scaled scrolling bargraph
    leadingSpaces = " " * (value * (SCREEN_WIDTH - 3) / 255)
    print "%s%3i" % (leadingSpaces, value)

def cheapoScope(serialPort):
    while(1):
        newValue = readValue(serialPort)
        plotValue(newValue)

if __name__ == "__main__":
    PORT = 'COM4'
    BAUDRATE = 9600
    TIMEOUT = None
    SCREEN_WIDTH = 80
    
    # Take command line args to override defaults above
    import sys
    if len(sys.argv) == 3:
        port = sys.argv[1]
        baudrate = int(sys.argv[2])
    else: # nothing passed, use defaults
        print ("Optional args port, baudrate set to defaults.")
        port, baudrate = (PORT, BAUDRATE)
    
    serialPort = serial.Serial(port, baudrate, timeout = TIMEOUT)
    serialPort.flush()
    cheapoScope(serialPort)