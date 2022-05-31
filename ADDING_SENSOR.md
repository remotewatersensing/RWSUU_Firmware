 
# Adding a new sensor to the package

Every sensor has a simple way of interacting with the system. In order to connect with the system, you need the following:

1. A function that initializes your sensor (Set the pin, handle first communication, etc.) - example: initAcidity()
This function is called in the setup() of the MCU.

2. (optional) a function that calibrates your sensor - example: calibAcidity()
This function can be called at the end of the setup() of your MCU

3. A function to retrieve the value - example: getAcidity()
This function is called in the loop and should return a float. If you are debugging, print these values out to the console.

4. A sensor ID in defines.h to indicate what sensor you are talking about
This ID has to be unique and sequential from the rest of the IDs. It is used when saving to the binary file and converting it back to a csv file.

If you have implemented the sensor, please proceed to update RWSUU_DAT2CSV with the new sensor ID at the string array: sensorId