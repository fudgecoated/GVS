from connector import find_connection
import struct
from time import sleep
import time
import threading

serial_connection = find_connection()

def write_integer(val):
    serial_connection.write(struct.pack('i', int(val)))

def write_float(val):
    serial_connection.write(struct.pack('f', float(val)))






class StreamData():

    def __init__(self, number_of_variables, connection):
        self.streaming_now = False
        self.data = []
        self.allData = []
        self.time_stamps = []
        self.streaming = True
        self.number_of_variables = number_of_variables
        for i in range(number_of_variables):
            self.data.append([])
        self.raw_data = bytearray(number_of_variables*4)
        self.connection = connection

    
    def start_streaming(self):
        write_integer(1)
        sleep(1)
        self.connection.reset_input_buffer()
        write_integer(4*self.number_of_variables)
        sleep(1)
        self.connection.reset_input_buffer()
        write_float(1.0)
        self.connection.reset_input_buffer()
        self.streaming_now = True
        while self.streaming:
            if self.connection.in_waiting:
                self.connection.readinto(self.raw_data)
                self.allData.append(self.raw_data)
                self.connection.reset_input_buffer()
                print(len(self.allData))

    def stop_streaming(self):
        self.streaming = False


data_stream = StreamData(8, serial_connection)
thread = threading.Thread(target = data_stream.start_streaming)
thread.daemon = True
thread.start()



while not data_stream.streaming_now:
    print("not streaming")


sleep(3)



data_stream.stop_streaming()


