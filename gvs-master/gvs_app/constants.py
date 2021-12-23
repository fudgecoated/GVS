class Constants:
    BAUD_RATE = 115200
    DEVELOPMENT_ADDRESS = '/dev/tty.usbmodemE0_6E_71_DD'            #Address for Micah's computer
    SIGNAL_TO_PROMPT_FOR_MODE = 42                                  #Arduino will send over integer 42 to prompt for mode
    START_SIGNAL = 41
    RESTART = 43
    PROMPT_FOR_GAIN = 45
    PAUSE = 46
    PROMPT_FOR_VOLTAGE = 44
    NUMBER_OF_FLOATS = 7
    NUMBER_OF_UNSIGNED_INTEGERS = 1
    NUMBER_OF_BYTES_PER_FLOAT = 4 