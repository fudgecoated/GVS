import struct
from constants import Constants
from time import sleep

class SerialInterface():

    def __init__(self, connection, mode):
        self.serial_connection = connection
        self.reading = True
        self.mode = mode
        self.time_stamps = []
        self.streaming = True

        self.voltage = []
        self.gyroX = []
        self.gyroY = []
        self.gyroZ = []
        self.accelX = []
        self.accelY = []
        self.accelZ = []

        self.raw_data = bytearray(Constants.NUMBER_OF_BYTES_PER_FLOAT* (Constants.NUMBER_OF_FLOATS + Constants.NUMBER_OF_UNSIGNED_INTEGERS))
        self.byte_holder = bytearray(4)

    def write_integer(self, val):
        self.serial_connection.write(struct.pack('i', int(val)))
    
    def write_float(self, val):
        self.serial_connection.write(struct.pack('f', float(val)))


    def set_mode(self, mode):
        self.mode = mode


    def pause_reading(self):
        self.write_integer(Constants.PAUSE)


    def stream_data(self):
        if self.mode[0] == "Steady Voltage":
            self.write_integer(1)
            self.write_float(self.mode[1])
        elif self.mode[0] == "Proportional Voltage":
            print("writing 2")
            self.write_integer(2)
            self.write_float(self.mode[1])
        else:
            self.write_integer(3)
        self.serial_connection.reset_input_buffer()
        i = 0
        while self.streaming:
            if self.serial_connection.in_waiting == 4 and i == 0:
                i = 1
                self.serial_connection.readinto(self.byte_holder)
                print(self.byte_holder)
                self.serial_connection.reset_input_buffer()
            
            if self.serial_connection.read(1) == b'\xff':
                self.serial_connection.readinto(self.raw_data)
                if self.serial_connection.read(1) == b'\xfe':
                    self.time_stamps.append(struct.unpack('I', self.raw_data[28:32])[0]/1000000)
                    self.voltage.append(struct.unpack('f', self.raw_data[0:4])[0])
                    self.gyroX.append(struct.unpack('f', self.raw_data[4:8])[0])
                    self.gyroY.append(struct.unpack('f', self.raw_data[8:12])[0])
                    self.gyroZ.append(struct.unpack('f', self.raw_data[12:16])[0])
                    self.accelX.append(struct.unpack('f', self.raw_data[16:20])[0])
                    self.accelY.append(struct.unpack('f', self.raw_data[20:24])[0])
                    self.accelZ.append(struct.unpack('f', self.raw_data[24:28])[0])
            else:
                print("missed sample")
                while self.serial_connection.read(1) != b'\xfe':
                    pass







"""



                if (timeStamp <= self.time_stamps[-1]+0.2) and (timeStamp >= self.time_stamps[-1]):
"""
#timeStamp = struct.unpack('f', self.raw_data[0V])
#for i in range(Constants.NUMBER_OF_FLOATS):
#    self.data[i].append(struct.unpack('f', self.raw_data[i*Constants.NUMBER_OF_BYTES_PER_FLOAT: Constants.NUMBER_OF_BYTES_PER_FLOAT + i * Constants.NUMBER_OF_BYTES_PER_FLOAT])[0])

#timeStamp = struct.unpack('f', self.raw_data[((Constants.NUMBER_OF_FLOATS)* Constants.NUMBER_OF_BYTES_PER_FLOAT): ((Constants.NUMBER_OF_FLOATS+Constants.NUMBER_OF_UNSIGNED_INTEGERS)* Constants.NUMBER_OF_BYTES_PER_FLOAT)])[0]
#self.time_stamps.append(timeStamp)