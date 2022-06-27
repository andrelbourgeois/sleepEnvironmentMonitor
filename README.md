# LCD Sleep Environment Monitor
CASA0016 Final Critique

By André Bourgeois

# Description
The intent of this project was to create a sensor system that would help to inform my understanding my sleeping environment throughout the night. Understanding that
temperature and light are important aspects of a sleeping environment, this build will be able to monitor the levels of these variables in my room, and make an
educated guess on the quality of my sleep. Although there are many other important aspects to one's sleep quality, I believe this build will provide a strong indication
on sleep quality with the chosen criteria. The resulting design was an iteration on previous projects that I completed throughout this course.

# The Process
**Prototype 1**

My first prototype for this project was [LEDstripURF](https://github.com/andrelbourgeois/CASA0016/tree/master/LEDstripURF). Using an ultrasonic range finder (URF) as an input, and an LED strip as an output, this sensor network was able to detect the distance of an object and visually display a value of this distance by lighting up the LEDs. A greater
distance from the URF results in more LEDs being lit up to represent the increased distance. I couldnèt find a real need for a URF in my life, so my first step was to replace
the sensor and choose something which I thought would add more value to my life than detecting distance - temperature.

![LEDstripURF](https://user-images.githubusercontent.com/33913141/144129281-4d4bb6da-3713-4bb9-be24-c0350a4b07c0.jpg)

**Prototype 2**

My second prototype for this project was [LEDstripTHERMOMETER](https://github.com/andrelbourgeois/CASA0016/tree/master/LEDstripTHERMOMETER). Very similar to the last protoype,
however, it uses a DHT22 temperature and humidity sensor (DHT22) as an input. The function of this build is similar, wherein a higher temperature will light up more LEDs to
represent the greater value. The next issues I realized was how inaccurate this LED strip was at relaying information, particularly values that exceed 8 (the number of LEDs
on the strip) or negative values. This is because the temperature value is mapped to the 8 LEDs. In my case, using a maxmimum temperature value of 40, each LED would represent
5 degrees - a fairly significant number. I decided it would be better to switch the LED strip for something a little more human-friendly.

![LEDstripTHERMOMETER](https://user-images.githubusercontent.com/33913141/144129314-a341689a-9762-4c7f-a57e-eb049f3dec82.jpg)

**Prototype 3**

In the third prototype for this build, [LCDtheremometer](https://github.com/andrelbourgeois/CASA0016/tree/master/LCDthermometer), I switched the LED strip from a liquid
crystal display (LCD) which I found was much more accurate, and much easier to read. It reduces the amount of mental math I need to do whenever I want to know the
temperature, and let's be honest - visually appealing.

![LCDthermometer](https://user-images.githubusercontent.com/33913141/144129329-fab20756-0b29-436e-a109-5b38f9693be5.jpg)

**Final Build**

For the final build, LCDsleepENVmonitor, I switched the DHT22 Temperature and Humidity Sensor for a simpler LM35 Temperature Sensor and added a Light Dependant resistor.
The goal of these two sensors, is to monitor the light and temperature of a room over several hours in the most simplistic way possible - without intaking any unnecessary data. Additionally, I added a toggle switch to change the LCD display from showing current light and temperature readings to average light and temperature readings and an estimated sleep quality. On a non-technical note, I added an enclosure made of tape and cardboard that is supposed to resemble a bed - complete with phyiscal documenation regarding what this device does as well as who to contact for more information.

![image](https://user-images.githubusercontent.com/33913141/146164067-ceca5c1d-6d43-4fef-b496-43499c5d8fd6.png)
![image](https://user-images.githubusercontent.com/33913141/146175116-bec4e09a-e5d8-4dcd-91bf-f985831a5596.png)
![image](https://user-images.githubusercontent.com/33913141/146163959-a48ca9de-e831-4371-ab26-a5999c735bd1.png)

# Materials
- Arduino Uno
- Breadboard
- Plastic Arduino Base
- Push Button
- USB Cable
- LM35 Temperature Sensor
- Light Dependant Resistor (LDR)
- LCD Screen
- Toggle Switch
- Potentiometer
- 220 Resistor
- 10k Resistor x2
- Wires

**Process**
- Build the circuit - Fritzing diagram developed with [Tinkercad](https://www.tinkercad.com)
![LCDsleepENVmonitor](https://user-images.githubusercontent.com/33913141/146167989-c9894a35-37c1-45f9-a3aa-a39177f68c22.png)
- Write the code\
For this application, the code is written to assume that optimal light levels are as low as possible, and optimal temperature levels are between 15-20°C.
- Build the enclosure


**Problems & Solutions**

- Problem: My LCD turned on my it's just a blank screen.\
Solution: Add a potentiometer which can adjust the resolution on the LCD.

- Problem: My temperature sensor was not giving a temperature value and instead, my LCD was reading "Nan".\
Solution: "Nan" stands for "Not a number" - I realized that the temperature value was staying a blank floating point number, and was not recieving a value from the DHT22.
I also realized that the DHT22 was not oriented properly. By rotating it 90° and adjusting the wires accordingly, I was able to recieve the correct value.

- Problem: LCD showing a lot of random  characters and symbols - looks like an alien language.\
Solution: I'm not actually sure what the issue is here, but unplugging the board and plugging it back into the computer fixes this issue every time

- Problem: Determining radiance in a similar way to the human eye.\
Solution: This build doesn't have to be as accurate as the human eye, and mapping the LDR reading in a linear fashion provided data that was accurate enough to estimate light levels in a room.\
According to my research, maximum Lx in a brightly lit room is ~ 1000, so by mapping that to the lowest reading on my LDR and mapping the highest LDR reading (1023) to 0, I was able to get an effective estimation of light levls and therefore, sleep quality.

**Course-Specific Highlights**
- Proper wiring conventions (Red for positive and green for ground)
- Effective device communication on enclosure\
- External battery
- Run-time with my battery\
The specific battery I used is 20100mAh, assuming the arduino is pulling ~50mA and the LCD screen is pulling ~1.1mA (these are estimations I found online), this build will run for ~ 393 hours, or ~16 days. However, assuming that this build is only ran over 8 hours of sleep per day, one could potentially go ~ 7 weeks between charging.
- Testing results: Light levels are generally below ~10Lx and temperature was usually ~18°C

**References**
- CASA0016 Course Material (general software and hardware information)
- Arduino Starter Kit Handbook (information specific to the LCD screen)
- [The Sleep Foundation](https://www.sleepfoundation.org/) (for information on optimal levels of light and temperature for sleep)

**Improvements**
- Add a curcuit diagram to README.md
- Improve step-by-step build instructions\
Section-off code and circuit builds to individual builds ie. Step 1 - Build temperature circuit + write temperature sensing code // step 5 - build LCD circuit and write code
- Adapt the build to a wifi-enabled board (arduino wifi rev2)\
Will allow me to send data via wifi to my raspberri pi and track trends with Grafana
- Improve enclosure by 3D printing + allocate internal space for battery + print out phyiscal communication instead of writing it
- Attach a dimmer or another switch to reduce LCD light when in operation
- Improve light detection code create a function to call for light and temperature readings - will limit code repetitiveness

