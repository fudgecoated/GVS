from tkinter import ttk
import tkinter as tk
import time
from connector import find_connection
import matplotlib.animation as animation
from matplotlib import style
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
from SerialInterface import SerialInterface
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from threading import Thread
from constants import Constants 

style.use('ggplot')
entry_value = {'Steady Voltage', 0}
connection = False
thread = False

fig = Figure(figsize=(5,4), dpi=100)
ax = fig.add_subplot(111)
print(ax)


def animate(i):
    timeStampList = []
    xList = []
    yList = []
    zList = []
    voltageList = []
    if connection and len(connection.time_stamps)>50:
        timeStampList = connection.time_stamps[-100:]
        xList = connection.gyroX[-100:]
        yList = connection.gyroY[-100:]
        zList = connection.gyroZ[-100:]
        voltageList = connection.voltage[-100:]


        """
        print("time\n")
        print(connection.time_stamps[-1])
        for i in range(Constants.NUMBER_OF_FLOATS):
            print("data "+str(i))
            print(connection.data[i][-1])
        """
    else:
        pullData = open("sampleData.txt", 'r').read()
        dataList = pullData.split('\n')

        for eachline in dataList:
            if len(eachline) > 1:
                x,y = eachline.split(',')
                timeStampList.append(int(x))
                xList.append(int(y))
                yList.append(int(y))
                zList.append(int(y))
                voltageList.append(int(y))
    ax.clear()
    ax.set_ylim(bottom=-3, top=3)
    ax.plot(timeStampList, xList, label="pitch")
    ax.plot(timeStampList, yList, label="roll")
    ax.plot(timeStampList, zList, label="yaw")
    ax.plot(timeStampList, voltageList, '--r', label="voltage")
    leg = ax.legend()


class GVSapp(tk.Tk):

    def __init__(self, *args, **kwargs):
        
        tk.Tk.__init__(self, *args, **kwargs)

        container = tk.Frame(self)

        container.pack(side="top", fill="both", expand = True)
        container.grid_rowconfigure(0,weight=1)
        container.grid_columnconfigure(0,weight=1)

        self.frames = {}

        for f in [StartPage, GraphPage, ConnectPage]:
            frame = f(container, self)
            self.frames[f] = frame
            frame.grid(row=0, column=0, sticky='nsew')

        self.show_frame(ConnectPage)



    def show_frame(self, cont):

        frame = self.frames[cont]

        frame.tkraise()


class GraphPage(tk.Frame):

    global entry_value
    global connection
    global thread

    def __init__(self, parent, controller):

        tk.Frame.__init__(self, parent)

        self.controller = controller

        label = tk.Label(self, text="Graph Page")
        label.pack()

        self.button = ttk.Button(self, text="Apply Voltage", command = self.start_graph)

        self.switch_mode_button = ttk.Button(self, text="Adjust Mode", command = self.switch_mode)

        self.kill_voltage_button = ttk.Button(self, text="Kill Voltage", command = self.kill_voltage)

        self.switch_mode_button.pack()

        self.kill_voltage_button.pack()

        self.button.pack()

        ax.plot([1,2,3,4,5,6,7,8], [5,6,1,3,8,9,3,5])

        ax.set_ylim(-3,3)

        self.canvas = FigureCanvasTkAgg(fig, self)

        self.canvas.draw()

        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)


    def switch_mode(self):
        print("switch window")
        connection.streaming = False
        connection.pause_reading()
        self.controller.show_frame(StartPage)



    def kill_voltage(self):
        """
        connection.streaming = False
        connection.serial_connection.reset_input_buffer()
        connection.pause_reading()
        time.sleep(1.0)
        connection.set_mode("No Voltage")
        thread = Thread(target = connection.stream_data)
        connection.streaming = True
        thread.start()
        """
        """
        connection.streaming = False
        connection.pause_reading()
        time.sleep(3)

        """
        self.setup_graph("No Voltage")

    def start_graph(self):
        self.button.grid_forget()
        self.setup_graph(entry_value)

    def setup_graph(self, mode):
        connection.streaming = True
        connection.set_mode(mode)
        thread = Thread(target=connection.stream_data)
        thread.start()


    

        

class ConnectPage(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        self.button = ttk.Button(self, text="Connect", command=self.connect)

        self.button.pack()

    def connect(self):
        global connection
        global entry_value
        serial_port = find_connection()
        if serial_port:
            connection = SerialInterface(serial_port, entry_value)
            self.controller.show_frame(StartPage)
        else:
            self.label = tk.Label(self, text="Connection to Serial Port was unsuccesful. Try Again")
            self.button.config(text="retry")
            self.label.pack()




class StartPage(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.controller = controller

        var = tk.StringVar(self)
        options = ["Steady Voltage", "Proportional Voltage"]
        option = ttk.OptionMenu(self, var, options[0], *options, command=self.popup)
        option.pack()

        self.button = ttk.Button(self, text="Ok", command= self.entry_value)
        self.button.pack()



    def popup(self, message):
        self.w=PopUpWindow(self.controller, message)
        self.button["state"] = "disabled" 
        self.master.wait_window(self.w.top)
        self.button["state"] = "normal"

    def entry_value(self):
        global entry_value
        entry_value = self.w.value
        self.controller.show_frame(GraphPage)
        GraphPage.setup_graph(app.frames[GraphPage], entry_value)



        



class PopUpWindow():
    def __init__(self,master, message):
        self.message = message
        if self.message == "Proportional Voltage":
            text = "Enter gain"
        else:
            text = "Enter voltage"

        top=self.top=tk.Toplevel(master)
        self.l=tk.Label(top,text=text)
        self.l.pack()
        self.e=tk.Entry(top)
        self.e.pack()
        self.b=ttk.Button(top,text='Ok',command=self.cleanup)
        self.b.pack()
    def cleanup(self):
        try:
            user_input = self.e.get()
            if self.message == "Proportional Voltage":
                user_input=int(self.e.get())
            else:
                user_input=float(self.e.get())
            self.value=[self.message, user_input]
            self.top.destroy()
        except:
            if self.message == "Proportional Voltage":
                self.l2 = tk.Label(self.top,text = "Input was not the correct format. Must be a integer")
            else:
                self.l2 = tk.Label(self.top,text = "Input was not the correct format. Must be a Float")
            self.l2.pack()



        

app = GVSapp()
ani = animation.FuncAnimation(fig,animate, interval = 150)
app.mainloop()
