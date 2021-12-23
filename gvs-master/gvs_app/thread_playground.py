from threading import Thread
from time import sleep

class Running_Thread():

    def __init__(self, word_to_print):
        self.word_to_print = word_to_print
        self.streaming = True 

    def turn_off(self):
        self.streaming = False

    def print_word(self):
        while self.streaming == True:
            print(self.word_to_print)



threadClass = Running_Thread("boobs")

thread = Thread(target=threadClass.print_word)

thread.start()

sleep(4)

threadClass.turn_off()

print(thread)
