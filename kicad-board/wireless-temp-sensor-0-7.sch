EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:wireless-temp-sensor-0-7-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "3 aug 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY84-P IC1
U 1 1 559D18EB
P 6450 3600
F 0 "IC1" H 5600 4350 40  0000 C CNN
F 1 "ATTINY84-P" H 7150 2850 40  0000 C CNN
F 2 "DIP14" H 6450 3400 35  0000 C CIN
F 3 "" H 6450 3600 60  0000 C CNN
	1    6450 3600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 559D1B6C
P 7800 3200
F 0 "R2" V 7880 3200 40  0000 C CNN
F 1 "4k7" V 7807 3201 40  0000 C CNN
F 2 "~" V 7730 3200 30  0000 C CNN
F 3 "~" H 7800 3200 30  0000 C CNN
	1    7800 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 559D1CAC
P 7800 3100
F 0 "R1" V 7880 3100 40  0000 C CNN
F 1 "68R" V 7807 3101 40  0000 C CNN
F 2 "~" V 7730 3100 30  0000 C CNN
F 3 "~" H 7800 3100 30  0000 C CNN
	1    7800 3100
	0    -1   -1   0   
$EndComp
$Comp
L ZENER D1
U 1 1 559D1D4C
P 8450 3100
F 0 "D1" H 8450 3200 50  0000 C CNN
F 1 "1N4729A" H 8450 3000 40  0000 C CNN
F 2 "~" H 8450 3100 60  0000 C CNN
F 3 "~" H 8450 3100 60  0000 C CNN
	1    8450 3100
	-1   0    0    1   
$EndComp
$Comp
L CONN_4X2 P2
U 1 1 559D1F78
P 9000 2200
F 0 "P2" H 9000 2450 50  0000 C CNN
F 1 "CONN_4X2" V 9000 2200 40  0000 C CNN
F 2 "" H 9000 2200 60  0000 C CNN
F 3 "" H 9000 2200 60  0000 C CNN
	1    9000 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 559D1FD8
P 9150 4000
F 0 "K1" V 9100 4000 50  0000 C CNN
F 1 "CONN_3" V 9200 4000 40  0000 C CNN
F 2 "" H 9150 4000 60  0000 C CNN
F 3 "" H 9150 4000 60  0000 C CNN
	1    9150 4000
	1    0    0    -1  
$EndComp
NoConn ~ 9400 2350
$Comp
L CONN_3X2 P1
U 1 1 55BA1EF0
P 8900 5000
F 0 "P1" H 8900 5250 50  0000 C CNN
F 1 "CONN_3X2" V 8900 5050 40  0000 C CNN
F 2 "" H 8900 5000 60  0000 C CNN
F 3 "" H 8900 5000 60  0000 C CNN
	1    8900 5000
	1    0    0    -1  
$EndComp
NoConn ~ 7500 3000
NoConn ~ 7500 3300
NoConn ~ 7500 3900
$Comp
L PWR_FLAG #FLG1
U 1 1 55BC1709
P 5250 2650
F 0 "#FLG1" H 5250 2745 30  0001 C CNN
F 1 "PWR_FLAG" H 5250 2830 30  0000 C CNN
F 2 "" H 5250 2650 60  0000 C CNN
F 3 "" H 5250 2650 60  0000 C CNN
	1    5250 2650
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 55BC1718
P 5400 4100
F 0 "#FLG2" H 5400 4195 30  0001 C CNN
F 1 "PWR_FLAG" H 5400 4280 30  0000 C CNN
F 2 "" H 5400 4100 60  0000 C CNN
F 3 "" H 5400 4100 60  0000 C CNN
	1    5400 4100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR1
U 1 1 55BC18A7
P 5400 2650
F 0 "#PWR1" H 5400 2750 30  0001 C CNN
F 1 "VCC" H 5400 2750 30  0000 C CNN
F 2 "" H 5400 2650 60  0000 C CNN
F 3 "" H 5400 2650 60  0000 C CNN
	1    5400 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 55BC18B6
P 5400 4450
F 0 "#PWR2" H 5400 4450 30  0001 C CNN
F 1 "GND" H 5400 4380 30  0001 C CNN
F 2 "" H 5400 4450 60  0000 C CNN
F 3 "" H 5400 4450 60  0000 C CNN
	1    5400 4450
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P3
U 1 1 55BC1FCA
P 4750 3750
F 0 "P3" V 4700 3750 40  0000 C CNN
F 1 "CONN_2" V 4800 3750 40  0000 C CNN
F 2 "" H 4750 3750 60  0000 C CNN
F 3 "" H 4750 3750 60  0000 C CNN
	1    4750 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K2
U 1 1 55BD7EE2
P 9550 4000
F 0 "K2" V 9500 4000 50  0000 C CNN
F 1 "CONN_3" V 9600 4000 40  0000 C CNN
F 2 "" H 9550 4000 60  0000 C CNN
F 3 "" H 9550 4000 60  0000 C CNN
	1    9550 4000
	-1   0    0    1   
$EndComp
$Comp
L CONN_3 K3
U 1 1 55BD7FD3
P 10350 2150
F 0 "K3" V 10300 2150 50  0000 C CNN
F 1 "CONN_3" V 10400 2150 40  0000 C CNN
F 2 "" H 10350 2150 60  0000 C CNN
F 3 "" H 10350 2150 60  0000 C CNN
	1    10350 2150
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 55BF4F9D
P 5300 3300
F 0 "C2" H 5300 3400 40  0000 L CNN
F 1 "100nF" H 5306 3215 40  0000 L CNN
F 2 "~" H 5338 3150 30  0000 C CNN
F 3 "~" H 5300 3300 60  0000 C CNN
	1    5300 3300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55BF4FAC
P 5100 3300
F 0 "C1" H 5100 3400 40  0000 L CNN
F 1 "1uF" H 5106 3215 40  0000 L CNN
F 2 "~" H 5138 3150 30  0000 C CNN
F 3 "~" H 5100 3300 60  0000 C CNN
	1    5100 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4100 5400 4450
Wire Wire Line
	8050 3100 8250 3100
Wire Wire Line
	8650 2700 8650 4400
Wire Wire Line
	8650 4400 5400 4400
Connection ~ 5400 4400
Wire Wire Line
	7550 3100 7500 3100
Wire Wire Line
	8150 2900 8150 3100
Connection ~ 8150 3100
Wire Wire Line
	8600 2050 8450 2050
Wire Wire Line
	8450 2050 8450 2700
Wire Wire Line
	8450 2700 8650 2700
Connection ~ 8650 3100
Wire Wire Line
	8200 2150 8600 2150
Wire Wire Line
	8200 2150 8200 3700
Wire Wire Line
	8200 3700 7500 3700
Wire Wire Line
	9400 2150 9750 2150
Wire Wire Line
	9750 2150 9750 5150
Wire Wire Line
	8500 4250 8500 4100
Wire Wire Line
	7500 3500 9550 3500
Wire Wire Line
	9550 3500 9550 2250
Wire Wire Line
	9550 2250 9400 2250
Wire Wire Line
	8600 2250 8300 2250
Wire Wire Line
	8300 2250 8300 3400
Wire Wire Line
	7500 3400 8400 3400
Wire Wire Line
	8600 2350 8600 2650
Wire Wire Line
	8600 2650 8750 2650
Wire Wire Line
	8750 2650 8750 3600
Wire Wire Line
	7500 3600 9400 3600
Connection ~ 8650 4100
Wire Wire Line
	8800 3900 8650 3900
Connection ~ 8650 3900
Wire Wire Line
	8500 4850 8500 3500
Connection ~ 8500 3500
Wire Wire Line
	5400 2850 4950 2850
Wire Wire Line
	4950 2850 4950 4600
Wire Wire Line
	4950 4600 9300 4600
Wire Wire Line
	9300 3900 9300 4850
Connection ~ 5400 2850
Wire Wire Line
	9400 3600 9400 4950
Wire Wire Line
	9400 4950 9300 4950
Connection ~ 8750 3600
Wire Wire Line
	9500 4250 9500 5050
Wire Wire Line
	9500 5050 9300 5050
Connection ~ 9500 4250
Wire Wire Line
	8400 3400 8400 4950
Wire Wire Line
	8400 4950 8500 4950
Connection ~ 8300 3400
Wire Wire Line
	7500 4200 8300 4200
Wire Wire Line
	8300 4200 8300 5050
Wire Wire Line
	8300 5050 8500 5050
Connection ~ 5400 4200
Wire Wire Line
	5400 2650 5250 2650
Wire Wire Line
	5400 2650 5400 3000
Wire Wire Line
	4950 3400 4400 3400
Wire Wire Line
	4400 3400 4400 3650
Connection ~ 4950 3400
Wire Wire Line
	4400 3850 4400 4300
Wire Wire Line
	4400 4300 5400 4300
Connection ~ 5400 4300
Wire Wire Line
	8650 4250 9900 4250
Connection ~ 8650 4250
Wire Wire Line
	7500 4100 8000 4100
Wire Wire Line
	8000 4100 8000 5150
Wire Wire Line
	8000 5150 9750 5150
Wire Wire Line
	7500 4000 8800 4000
Wire Wire Line
	7500 3200 7550 3200
Wire Wire Line
	8050 3200 8050 4000
Connection ~ 8050 4000
Wire Wire Line
	8800 4100 9600 4100
Wire Wire Line
	9600 4100 9600 4000
Wire Wire Line
	9600 4000 9900 4000
Wire Wire Line
	9900 4250 9900 4100
Wire Wire Line
	9300 3900 9900 3900
Connection ~ 9300 4600
Wire Wire Line
	9400 2050 9900 2050
Wire Wire Line
	9900 2050 9900 2150
Wire Wire Line
	9900 2150 10000 2150
Wire Wire Line
	10000 2000 10000 2050
Connection ~ 9650 3900
Wire Wire Line
	10000 2250 9650 2250
Wire Wire Line
	9650 2250 9650 3900
Wire Wire Line
	10000 2000 9800 2000
Wire Wire Line
	9800 2000 9800 2900
Connection ~ 9800 2900
Wire Wire Line
	9800 2900 8150 2900
Wire Wire Line
	5300 3100 5300 2850
Connection ~ 5300 2850
Wire Wire Line
	5100 3100 5100 2850
Connection ~ 5100 2850
Wire Wire Line
	5300 3500 5300 4300
Connection ~ 5300 4300
Wire Wire Line
	5100 3500 5100 4300
Connection ~ 5100 4300
$EndSCHEMATC
