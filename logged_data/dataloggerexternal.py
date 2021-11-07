# FRASER MONTANDON
# external ADC logger for testing
#!/usr/bin/python

import spidev
import RPi.GPIO as GPIO
import time
from datetime import datetime
import os

# GPIO setup
GPIO.setmode (GPIO.BCM)
GPIO.setwarnings(False)

switch = 18
GPIO.setup(switch, GPIO.IN)

#Define Variables
delay = 0.5


#Create SPI
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz=1000000

def readadc(adcnum):
    # read SPI data from the MCP3008, 8 channels in total
    if adcnum > 7 or adcnum < 0:
        return -1
    r = spi.xfer2([1, 8 + adcnum << 4, 0])
    data = ((r[1] & 3) << 8) + r[2]
    return data


print('Reading MCP3008 values, press Ctrl-C to quit...')
# Print nice channel column headers.
print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*range(8)))
print('-' * 57)
# Main program loop.
while True:
    while GPIO.input(switch) == 1:
        time.sleep (0.5)
        
    results = ""
    # Read all the ADC channel values in a list.
    values = [0]*8
    for i in range(8):
        # The read_adc function will get the value of the specified channel (0-7).
        values[i] = readadc(i)

        results = results + str(values[i]) + ","

    results = results  + "\n"
        
    # Print the ADC values.
    print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*values))
    # Pause for one second.
    time.sleep(1)

    with open("/home/pi/data_log.csv", "a") as file:
            if os.stat("/home/pi/data_log.csv").st_size == 0:
                file.write("CH0,CH1,CH2,CH3,CH4,CH5,CH6,CH7\n")
            file.write(results)
            time.sleep (0.5)