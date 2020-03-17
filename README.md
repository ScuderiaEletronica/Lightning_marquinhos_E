# Lightning_marquinhos_E
## Introduction

This project uses an ESP32 to control the actuators and sensors from the RM-02 FSAE car,it's very important to pay attention to the list of the pins below in order to assembly the harness in the car. 
For futher instructions see the guides made for the Eletronics professionals.
This includes the following:

- [Engineering Report]()
- [Maintenance Manual]()
- [Troubleshoot (Hardware)]()
- [Troubleshoot (Software)]()




## Overall diagram from ESP 32 #TODO 

|**+3.3V**               	| 1  	| 2  	|**+5V**                  	|
|---------------------	|----	|----	|-----------------------	|
| SDA (I2C)           	| 3  	| 4  	| **+5V**                   	|
| SCL (I2C)           	| 5  	| 6  	| **GND**                   	|
| **Sensor de temperatura** | 7  	| 8  	| **Sensor 1**             	|
| **GND**               	| 9  	| 10 	| **Sensor 2**             	|
|**Acionamento Relé 1**| 11 	| 12 	| **Acionamento Relé 2**   	|
|**Sensor energia**        | 13 	| 14 	| **GND**                   	|
|**Acionamento Relé 3**   | 15 	| 16 	| **Acionamento Relé 4**      	|
| **+3.3V**               	   | 17 	| 18 	| GPIO24                	|
| **Sensor 3** 	   | 19 	| 20 	| **GND**                   	|
| GPIO9               	   | 21 	| 22 	| GPIO25                	|
| GPIO11              	| 23 	| 24 	| GPIO8                 	|
|**GND**                 	| 25 	| 26 	| GPIO7                 	|
| DNC                 	| 27 	| 28 	| DNC                   	|
| GPIO5               	| 29 	| 30 	| **GND**                   	|
| GPIO6               	| 31 	| 32 	| **Sinaleira entrada (moema)**    	|
| **Sinaleira saída (moema)**     	| 33 	| 34 	| **GND**                   	|
| GPIO19              	| 35 	| 36 	| GPIO16                	|
| **Cor R**          	| 37 	| 38 	| **Cor G**                	|
| **GND**                 	| 39 	| 40 	| **Cor B**                 |



## Pinout from ESP32

![esp32](https://user-images.githubusercontent.com/56930695/76874143-83ba0c00-684d-11ea-9d0a-b79af64e23a2.png)

## Prerequisites 

You should have to install some packages from pip3, to do that press **Ctrl+Alt+T** and type the following

```
colocar steps para rodar telemetria e monitoramento no carro,e software de tuning

```

## How to run the code

To run the code you must be in the following directory then you start the program with **python3 Main.py**

```

sudo systemctl start (programa para rodar a telemetria

```
## In case of hardware/software update

If is necessary to change the actuators pins, and other variables you will need to update the code, to do that edit in the VisualStudioCode the ' Config.py '  file, some possible changes are listed below:


## Support and Feedback
Sanic enterprises
