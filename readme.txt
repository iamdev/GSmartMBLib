Modbus Register Address : Holding Register
----------------------------------------------------
Addr  | Fn | Len | Type | Description
----------------------------------------------------
40001 | RO | 1   | U16  | Product Id
40002 | RO | 1   | U16  | Product Version
40003 | RW | 1   | U16  | Unit Id (1-254)
40004 | RW | 1   | U16  | Rate (Refer Buad reate table)
40005 | RW | 2   | F    | Analog Reference Delta (default=0, REF= 1.25v)
----------------------------------------------------

40601 | RW | 2   | U32  | Local Date Time (Unix Time)
40603 | W  | 2   | U32  | Set DATE [HEX: yyyy, mmdd]
40605 | W  | 2   | U32  | Set TIME [HEX: hh, mmss]

Relay Controll
----------------------------------------------------
41000 | RW | 1   | U16  | SET RELAY 6 BIT [00XX XXXX][X:0=OFF,X:1=ON]  
41001 | RW | 1   | U16  | RELAY 1 [0:ON|1:OFF]
41002 | RW | 1   | U16  | RELAY 2 [0:ON|1:OFF]
41003 | RW | 1   | U16  | RELAY 3 [0:ON|1:OFF]
41004 | RW | 1   | U16  | RELAY 4 [0:ON|1:OFF]
41005 | RW | 1   | U16  | RELAY 5 [0:ON|1:OFF]
41006 | RW | 1   | U16  | RELAY 6 [0:ON|1:OFF]
42001 | WO | 1   | U16  | Toggle RELAY 1
42002 | WO | 1   | U16  | Toggle RELAY 2
42003 | WO | 1   | U16  | Toggle RELAY 3
42004 | WO | 1   | U16  | Toggle RELAY 4
42005 | WO | 1   | U16  | Toggle RELAY 5
42006 | WO | 1   | U16  | Toggle RELAY 6
43001 | RO | 2   | F    | READ ANALOG CH 1
43002 | RO | 2   | F    | READ ANALOG CH 2
43003 | RO | 2   | F    | READ ANALOG CH 3
43004 | RO | 2   | F    | READ ANALOG CH 4
44001 | RW | 1   | U16  | DIGITAL I/O D0 STATE 
44002 | RW | 1   | U16  | DIGITAL I/O D1 STATE 
44003 | RW | 1   | U16  | DIGITAL I/O D2 STATE 
44004 | RW | 1   | U16  | DIGITAL I/O D3 STATE 
44005 | RW | 1   | U16  | DIGITAL I/O D4 STATE 
44006 | RW | 1   | U16  | DIGITAL I/O D5 STATE 
44007 | RW | 1   | U16  | DIGITAL I/O D6 STATE 
44008 | RW | 1   | U16  | DIGITAL I/O D7 STATE 
44009 | W  | 1   | U16  | TURN ON BUZZER FOR MILISECONDS
44011 | RW | 1   | U16  | DIGITAL I/O D0 MODE
44012 | RW | 1   | U16  | DIGITAL I/O D1 MODE
44013 | RW | 1   | U16  | DIGITAL I/O D2 MODE
44014 | RW | 1   | U16  | DIGITAL I/O D3 MODE
44015 | RW | 1   | U16  | DIGITAL I/O D4 MODE
44016 | RW | 1   | U16  | DIGITAL I/O D5 MODE
44017 | RW | 1   | U16  | DIGITAL I/O D6 MODE
44018 | RW | 1   | U16  | DIGITAL I/O D7 MODE
44019 | WO | 1   | U16  | Save IO Modes         

44021 | RW | 2   | U16  | SET PWM FREQUENCY CH1
44023 | RW | 2   | U16  | SET PWM FREQUENCY CH2 
44025 | RW | 2   | F    | Analog voltage reference delta

----------------------------------------------------


Digital I/O State Value:
----------------------------------------------------
Mode: I/O  Value : 0/1
Mode: PWM  Value : 0 to 10000 [DIV 100](0.00% - 100.00%)

Baud rate table
----------------------------------------------------
1  | 1200
2  | 2400
3  | 4800
4  | 9600 (default)
5  | 19200
6  | 38400
7  | 57600
8  | 74880
9  | 115200
10 | 230400
11 | 250000

IO Mode table
----------------------------------------------------
0 | INPUT PULL-UP
1 | OUTPUT
2 | PWM
3 | INPUT FLOATING
