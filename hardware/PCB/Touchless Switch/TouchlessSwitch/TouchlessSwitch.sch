EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Converter_ACDC:HLK-PM03 MOD1
U 1 1 6059EC6E
P 3300 1900
F 0 "MOD1" H 3400 2250 50  0000 C CNN
F 1 "HLK-PM03" H 3500 2150 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 3300 1600 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=59" H 3700 1550 50  0001 C CNN
	1    3300 1900
	1    0    0    -1  
$EndComp
$Comp
L Espressif:ESP32-PICO-KITv4_v4.1 MOD3
U 1 1 6059F944
P 7450 1250
F 0 "MOD3" H 7450 1322 50  0000 C CNN
F 1 "ESP32-PICO-KITv4_v4.1" H 7450 1231 50  0000 C CNN
F 2 "ESP32-PICO-KIT:DIP-40_W17.78mm_Socket" H 7450 1250 50  0001 C CNN
F 3 "" H 7450 1250 50  0001 C CNN
	1    7450 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 605A1F7B
P 3800 2450
F 0 "#PWR0101" H 3800 2200 50  0001 C CNN
F 1 "GND" H 3805 2277 50  0000 C CNN
F 2 "" H 3800 2450 50  0001 C CNN
F 3 "" H 3800 2450 50  0001 C CNN
	1    3800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2000 3800 2000
Wire Wire Line
	3800 2000 3800 2350
Connection ~ 3800 2350
Wire Wire Line
	3800 2350 3800 2450
$Comp
L Device:C_Small C2
U 1 1 605A7BED
P 8250 3250
F 0 "C2" H 8158 3204 50  0000 R CNN
F 1 "10uF / 6.3V" H 8158 3295 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 8250 3250 50  0001 C CNN
F 3 "~" H 8250 3250 50  0001 C CNN
	1    8250 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8150 3250 8100 3250
$Comp
L power:+3V3 #PWR0103
U 1 1 605ABD58
P 6800 1250
F 0 "#PWR0103" H 6800 1100 50  0001 C CNN
F 1 "+3V3" H 6815 1423 50  0000 C CNN
F 2 "" H 6800 1250 50  0001 C CNN
F 3 "" H 6800 1250 50  0001 C CNN
	1    6800 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3150 6800 3150
Wire Wire Line
	6950 3250 6650 3250
Wire Wire Line
	6650 3250 6650 3750
Wire Wire Line
	8350 3250 8450 3250
Wire Wire Line
	8450 3250 8450 3150
Wire Wire Line
	8450 3150 7950 3150
Wire Wire Line
	8100 3250 8100 3750
Wire Wire Line
	8100 3750 6650 3750
Connection ~ 8100 3250
Wire Wire Line
	8100 3250 7950 3250
Connection ~ 6650 3750
Wire Wire Line
	6650 3750 6650 3800
$Comp
L Relay:ADW11 RE1
U 1 1 605B7F3A
P 3300 3550
F 0 "RE1" H 3450 3300 50  0000 R CNN
F 1 "ADW11" H 3600 3950 50  0000 R CNN
F 2 "Relay_THT:Relay_1P1T_NO_10x24x18.8mm_Panasonic_ADW11xxxxW_THT" H 4625 3500 50  0001 C CNN
F 3 "https://www.panasonic-electric-works.com/pew/es/downloads/ds_dw_hl_en.pdf" H 3300 3550 50  0001 C CNN
	1    3300 3550
	-1   0    0    -1  
$EndComp
Text Notes 3850 1750 0    50   ~ 0
3W / 0.9A @ 3.3V out max
Wire Wire Line
	3500 3850 3500 3900
Wire Wire Line
	3500 3150 3500 3250
$Comp
L Connector_Generic:Conn_02x20_Odd_Even K3
U 1 1 605F20A6
P 9650 2300
F 0 "K3" H 9700 3350 50  0000 C CNN
F 1 "Pinheader" H 9700 1150 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 9650 2300 50  0001 C CNN
F 3 "~" H 9650 2300 50  0001 C CNN
	1    9650 2300
	1    0    0    -1  
$EndComp
Text GLabel 10250 1400 2    50   Input ~ 0
5V
Wire Wire Line
	9950 1400 10100 1400
Wire Wire Line
	9950 1500 10100 1500
Wire Wire Line
	10100 1500 10100 1400
Connection ~ 10100 1400
Wire Wire Line
	10100 1400 10250 1400
$Comp
L power:+3V3 #PWR0108
U 1 1 605F8D3D
P 9400 1250
F 0 "#PWR0108" H 9400 1100 50  0001 C CNN
F 1 "+3V3" H 9415 1423 50  0000 C CNN
F 2 "" H 9400 1250 50  0001 C CNN
F 3 "" H 9400 1250 50  0001 C CNN
	1    9400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1400 9400 1400
Wire Wire Line
	9400 1400 9400 1250
Wire Wire Line
	9450 2200 9400 2200
Wire Wire Line
	9400 2200 9400 1400
Connection ~ 9400 1400
Wire Wire Line
	9950 3000 10450 3000
Wire Wire Line
	10450 3000 10450 3500
Wire Wire Line
	9950 2800 10450 2800
Wire Wire Line
	10450 2800 10450 3000
Connection ~ 10450 3000
Wire Wire Line
	9950 2300 10450 2300
Wire Wire Line
	10450 2300 10450 2800
Connection ~ 10450 2800
Wire Wire Line
	9950 2000 10450 2000
Wire Wire Line
	10450 2000 10450 2300
Connection ~ 10450 2300
Wire Wire Line
	9950 1600 10450 1600
Wire Wire Line
	10450 1600 10450 2000
Connection ~ 10450 2000
Wire Wire Line
	9450 1800 9350 1800
Wire Wire Line
	9350 1800 9350 2600
Wire Wire Line
	9350 2600 9450 2600
$Comp
L Connector:Screw_Terminal_01x02 K1
U 1 1 60617522
P 1250 1800
F 0 "K1" H 1150 1650 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 900 1950 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1250 1800 50  0001 C CNN
F 3 "~" H 1250 1800 50  0001 C CNN
	1    1250 1800
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 K2
U 1 1 60618DA7
P 1250 2200
F 0 "K2" H 1150 2250 50  0000 C CNN
F 1 "Screw_Terminal_01x02" V 1250 2700 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1250 2200 50  0001 C CNN
F 3 "~" H 1250 2200 50  0001 C CNN
	1    1250 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 2100 2850 2000
Wire Wire Line
	2850 2000 2900 2000
Wire Wire Line
	2850 2100 2850 2200
Wire Wire Line
	2850 2200 1450 2200
Connection ~ 2850 2100
Text Notes 1100 1900 0    50   ~ 0
L
Text Notes 1100 2200 0    50   ~ 0
N
Wire Notes Line
	3300 4150 1050 4150
Wire Notes Line
	1050 4150 1050 1300
Wire Notes Line
	1050 1300 3300 1300
Wire Notes Line
	3300 1300 3300 4150
Text Notes 2600 1250 0    50   ~ 0
Mains section
Wire Wire Line
	7950 1750 8500 1750
Wire Wire Line
	9450 1500 8500 1500
Wire Wire Line
	8500 1500 8500 1750
Wire Wire Line
	8600 1850 8600 1600
Wire Wire Line
	8600 1600 9450 1600
Wire Wire Line
	7950 1850 8600 1850
Wire Wire Line
	7950 2150 8500 2150
Wire Wire Line
	8500 2150 8500 2500
Wire Wire Line
	8500 2500 9450 2500
Wire Wire Line
	7950 1950 8600 1950
Wire Wire Line
	8600 1950 8600 2400
Wire Wire Line
	8600 2400 9450 2400
Wire Wire Line
	9450 2300 8700 2300
Wire Wire Line
	8700 2300 8700 2050
Wire Wire Line
	8700 2050 7950 2050
Text GLabel 10200 2700 2    50   Input ~ 0
T_CS
Text GLabel 10200 2600 2    50   Input ~ 0
CS
Text GLabel 10200 2500 2    50   Input ~ 0
RST
Text GLabel 10200 2400 2    50   Input ~ 0
DC
Wire Wire Line
	9950 2700 10200 2700
Wire Wire Line
	10200 2600 9950 2600
Wire Wire Line
	10200 2400 9950 2400
Wire Wire Line
	9950 2500 10200 2500
Text GLabel 8200 2450 2    50   Input ~ 0
T_CS
Text GLabel 8200 2250 2    50   Input ~ 0
CS
Text GLabel 8200 2350 2    50   Input ~ 0
DC
Wire Wire Line
	8200 2350 7950 2350
Text GLabel 8700 3150 2    50   Input ~ 0
RST
Wire Wire Line
	7950 2450 8200 2450
Wire Wire Line
	8200 2250 7950 2250
Wire Wire Line
	1450 1900 1700 1900
Wire Wire Line
	1700 1900 1700 3850
$Comp
L Device:D D2
U 1 1 606140AD
P 3800 3500
F 0 "D2" H 3650 3550 50  0000 C CNN
F 1 "1N4001" H 3900 3600 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 3800 3500 50  0001 C CNN
F 3 "~" H 3800 3500 50  0001 C CNN
	1    3800 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 3850 3100 3850
Wire Wire Line
	3500 3150 3800 3150
Wire Wire Line
	3800 3150 3800 3350
Wire Wire Line
	3800 3650 3800 3900
Wire Wire Line
	3800 3900 3500 3900
$Comp
L power:GND #PWR0106
U 1 1 60654EB1
P 3800 4500
F 0 "#PWR0106" H 3800 4250 50  0001 C CNN
F 1 "GND" H 3805 4327 50  0000 C CNN
F 2 "" H 3800 4500 50  0001 C CNN
F 3 "" H 3800 4500 50  0001 C CNN
	1    3800 4500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC337 T1
U 1 1 606986AF
P 3900 4100
F 0 "T1" H 4091 4146 50  0000 L CNN
F 1 "BC337" H 4091 4055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4100 4025 50  0001 L CIN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bc337.pdf" H 3900 4100 50  0001 L CNN
	1    3900 4100
	-1   0    0    -1  
$EndComp
Connection ~ 3800 3900
$Comp
L Device:R_Small R1
U 1 1 606A6FD4
P 4500 4100
F 0 "R1" V 4696 4100 50  0000 C CNN
F 1 "1kR" V 4605 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 4500 4100 50  0001 C CNN
F 3 "~" H 4500 4100 50  0001 C CNN
	1    4500 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 4300 3800 4500
Wire Wire Line
	4100 4100 4400 4100
Wire Wire Line
	4950 1800 4950 3150
Wire Wire Line
	5050 2350 5050 1900
Wire Wire Line
	5150 2000 5150 4100
Wire Wire Line
	4600 4100 5150 4100
Wire Wire Line
	8450 3150 8700 3150
Text GLabel 9200 1700 0    50   Input ~ 0
INT
Wire Wire Line
	9200 1700 9450 1700
Text GLabel 9200 1900 0    50   Input ~ 0
MGC_RST
Wire Wire Line
	9200 1900 9450 1900
Text GLabel 6700 1950 0    50   Input ~ 0
INT
Wire Wire Line
	6700 1950 6950 1950
Text GLabel 6700 2050 0    50   Input ~ 0
MGC_RST
Wire Wire Line
	6700 2050 6950 2050
Text GLabel 6350 3350 0    50   Input ~ 0
5V
$Comp
L power:GND1 #PWR0102
U 1 1 607CBE33
P 6650 3800
F 0 "#PWR0102" H 6650 3550 50  0001 C CNN
F 1 "GND1" H 6655 3627 50  0000 C CNN
F 2 "" H 6650 3800 50  0001 C CNN
F 3 "" H 6650 3800 50  0001 C CNN
	1    6650 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR0104
U 1 1 607DA45D
P 9350 3500
F 0 "#PWR0104" H 9350 3250 50  0001 C CNN
F 1 "GND1" H 9355 3327 50  0000 C CNN
F 2 "" H 9350 3500 50  0001 C CNN
F 3 "" H 9350 3500 50  0001 C CNN
	1    9350 3500
	1    0    0    -1  
$EndComp
Connection ~ 9350 2600
Wire Wire Line
	9350 3500 9350 2600
$Comp
L power:GND1 #PWR0105
U 1 1 607F3DCB
P 10450 3500
F 0 "#PWR0105" H 10450 3250 50  0001 C CNN
F 1 "GND1" H 10455 3327 50  0000 C CNN
F 2 "" H 10450 3500 50  0001 C CNN
F 3 "" H 10450 3500 50  0001 C CNN
	1    10450 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2850 6650 3250
Connection ~ 6650 3250
Wire Wire Line
	6700 2750 6700 2950
Wire Wire Line
	6700 2950 6950 2950
Wire Wire Line
	6800 1250 6800 3050
Wire Wire Line
	6450 2950 6600 2950
Wire Wire Line
	6600 2950 6600 3050
Wire Wire Line
	6600 3050 6800 3050
Connection ~ 6800 3050
Wire Wire Line
	6800 3050 6800 3150
Wire Wire Line
	6350 3350 6450 3350
Wire Wire Line
	6450 3000 6450 2950
Connection ~ 6450 2950
Wire Wire Line
	6450 3300 6450 3350
Connection ~ 6450 3350
Wire Wire Line
	6450 3350 6950 3350
Text GLabel 6000 2750 0    50   Input ~ 0
RE_OUT
Text GLabel 5550 1800 2    50   Input ~ 0
3V3_IN
Text GLabel 5550 1900 2    50   Input ~ 0
GND_IN
Text GLabel 5550 2000 2    50   Input ~ 0
RE_OUT
Text GLabel 6000 2850 0    50   Input ~ 0
GND_IN
Text GLabel 6000 2950 0    50   Input ~ 0
3V3_IN
Wire Wire Line
	6450 2950 6000 2950
Wire Wire Line
	5150 2000 5550 2000
Wire Wire Line
	5050 1900 5550 1900
Connection ~ 4950 1800
Wire Wire Line
	6000 2850 6650 2850
Wire Wire Line
	6000 2750 6700 2750
Wire Wire Line
	3800 2350 4300 2350
Wire Wire Line
	3700 1800 4300 1800
$Comp
L Device:CP1_Small C1
U 1 1 60755977
P 4300 2100
F 0 "C1" H 4391 2146 50  0000 L CNN
F 1 "100µF/10V" H 4391 2055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4300 2100 50  0001 C CNN
F 3 "~" H 4300 2100 50  0001 C CNN
	1    4300 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2000 4300 1800
Connection ~ 4300 1800
Wire Wire Line
	4300 2200 4300 2350
Connection ~ 4300 2350
Wire Wire Line
	4300 2350 5050 2350
Connection ~ 8450 3150
Wire Wire Line
	1450 1800 1900 1800
Wire Wire Line
	1900 1800 1900 3250
Wire Wire Line
	1900 3250 3000 3250
Connection ~ 1900 1800
Wire Wire Line
	1450 2100 2850 2100
Wire Wire Line
	1900 1800 2900 1800
$Comp
L Device:D_Schottky D1
U 1 1 606C7F19
P 6450 3150
F 0 "D1" V 6500 3350 50  0000 R CNN
F 1 "1N5817" V 6400 3500 50  0000 R CNN
F 2 "Diode_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 6450 3150 50  0001 C CNN
F 3 "~" H 6450 3150 50  0001 C CNN
	1    6450 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 1800 5550 1800
Wire Wire Line
	4300 1800 4950 1800
Wire Wire Line
	3800 3150 4950 3150
Connection ~ 3800 3150
$EndSCHEMATC
