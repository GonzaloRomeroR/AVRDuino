We probably should add some markdown styling and proper explanations
for  each command below

####NodeMCU
ampy -p /dev/ttyUSB0 put boot.py
picocom /dev/ttyUSB0 -b 115200


####ARDUINO
cu -l /dev/ttyACM0 -s 9600
