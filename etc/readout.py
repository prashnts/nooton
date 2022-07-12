import time
import math
import board
import busio
import adafruit_ads1x15.ads1015 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Create the I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

# Create the ADC object using the I2C bus
ads = ADS.ADS1015(i2c)

# Create single-ended input on channel 0
chan = AnalogIn(ads, ADS.P0)

print("{:>5}\t{:>5}".format('raw', 'v'))


plt.style.use('seaborn')

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

plt.ylim([0, 3.3])
plt.autoscale(False)
xs = []
ys = []


def animate(i, xs, ys):

    v_a0 = v if (v := chan.voltage) >= 0 else 0
    xs.append(time.time())
    ys.append(v_a0)

    # Limit x and y lists to 20 items
    xs = xs[-50:]
    ys = ys[-50:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    # plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.ylim([0, 3.3])

    plt.title('FSR Response')
    plt.ylabel('Relative Force')

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=20)
plt.show()
