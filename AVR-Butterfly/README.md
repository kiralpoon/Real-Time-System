#Instruction of testing AVR-butterfly

**Make sure your Linux machine install the library we need for this project**

	bash
	apt-get install avr-libc gcc-avr gdb-avr avrdude


**To check is it flash ready**

	avrdude -p m169 -c butterfly -P /dev/ttyUSB0 -v
	

**Flashing Helloworld to the board**

* Download helloworld from jacky webpage

* Make sure to uncomment the code and change the port parameter to ttyusb0

**Compile and run**


	make clean
	make program


* Move the joystick up and you should able to see HelloWorld
* If permission is needed just add sudo

**Debug**

	dmesg //can be used to see what your compter connect the device
	lsusb //or this 

**Problems and Tips**
 * if the battery is nearly dead, the microcontroller will not be able to either Reading or erasing chip properly.
 * you can conveniently connect on the ISP GND and RST to reset the running program which makes it ready to program, instead of taking out thebattery or press the yellow button(if there is) to give the same effect .

**Current board status**
 * 11 boards with microphones are working, and 6 with battery. All are flashed to “Hello World”
 * 7 boards without microphones are working and all have battery.
 * Total of 18 boards are available.
 * 1 is used by TA: Kiral for testing 
 * Note that some batteries are dieing, so recommend student to get some new battery for the board

