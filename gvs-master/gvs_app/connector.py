import sys
import glob
import serial
import struct
from threading import Thread, Timer
from constants import Constants
from time import sleep



class Connection_atempt:
    """
    Object to run connection attempts for each port
    """
    def __init__(self, port_name):
        self.running = True                                                     
        self.connection = serial.Serial(port_name, Constants.BAUD_RATE)         #create serial connection
        self.connection_found = False
    
    def terminate(self):
        """Terminate thread when connection is found"""
        self.running = False
    
    def run(self):
        """Attempt to read byte from serial port until thread is terminated"""
        while self.running:
            rawData = bytearray(4)
            self.connection.readinto(rawData)                   #Try to read 4 bytes from port
            self.signal = struct.unpack('i', rawData)[0]        #decode the bytes to int
            if self.signal == Constants.START_SIGNAL:           #if signal is the one expected from arduino
                self.connection_found = True                        #Set flag to true

            






def find_connection():
    """Connects to serial port connected to gvs

    :returns:
        False if gvs arduino is not availible
        Serial object for gvs arduino if connection was found 
    """

    #Get a list of ports which could be wixel
    possible_candidates = serial_ports()
    print(possible_candidates)

    connection_atempts = list()
    threads = list()

    #Create a thread for each possible port
    for port in possible_candidates:
        con_attempt = Connection_atempt(port)
        connection_atempts.append(con_attempt)
        t = Thread(target = con_attempt.run)
        t.start()
        threads.append(t)

    #Wait for thread to attempt connection for a while
    sleep(5)

    connection = False

    for atempt in connection_atempts:
        if(atempt.connection_found):                        #Set connection to correct Serial connection
            connection = atempt.connection

        atempt.terminate()                                  #quit all unsuccessful threads
        atempt.connection.cancel_read()                     #Stop trying to read from port

    #Make sure threads are done
    for thread in threads:
        thread.join()

    return connection




def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

