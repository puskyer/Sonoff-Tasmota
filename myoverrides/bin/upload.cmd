rem only erase sketch space
rem C:\Users\Public\arduino-1.8.5\portable\packages\esp8266\tools\esptool\2.5.0-3-20ed2b9/esptool.exe -vv -cd ck -cb 115200 -cp COM3 -ca 0x00000 -cf  sonoff.ino.6.4.1.19.bin
rem erase all flash - sketch and wifi
rem C:\Users\Public\arduino-1.8.5\portable\packages\esp8266\tools\esptool\2.5.0-3-20ed2b9/esptool.exe -vv -cd ck -cb 115200 -cp COM3 -ca 0x0 -cz 0x100000 -ca 0x00000 -cf  sonoff.ino.6.4.1.19.1kflash.bin
C:\Users\pasqu\Documents\ArduinoData\packages\esp8266\tools\python\3.7.2-post1/python C:\Users\pasqu\Documents\ArduinoData\packages\esp8266\hardware\esp8266\2.5.2/tools/upload.py --chip esp8266 --port COM3 --baud 115200 --trace version --end --chip esp8266 --port COM3 --baud 115200 --trace write_flash 0x0 C:\Users\pasqu\AppData\Local\Temp\arduino_build_847539/sonoff.ino.bin --end 
