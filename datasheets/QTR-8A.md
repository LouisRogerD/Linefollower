Functional Description

The QTR-8A reflectance sensor array is intended as a line sensor, but it can be used as a general-purpose proximity or reflectance sensor. 
The module is a convenient carrier for eight IR emitter and receiver (phototransistor) pairs evenly spaced at intervals of 0.375″ (9.525 mm). 
Each phototransistor is connected to a pull-up resistor to form a voltage divider that produces an analog voltage output between 0 V and VIN (which is typically 5 V) as a function of the reflected IR.
Lower output voltage is an indication of greater reflection.

The outputs are all independent, but the LEDs are arranged in pairs to halve current consumption. 
The LEDs are controlled by a MOSFET with a gate normally pulled high, allowing the LEDs to be turned off by setting the MOSFET gate to a low voltage. 
Turning the LEDs off might be advantageous for limiting power consumption when the sensors are not in use or for varying the effective brightness of the LEDs through PWM control.

The LED current-limiting resistors for 5 V operation are arranged in two stages; this allows a simple bypass of one stage to enable operation at 3.3 V.
The LED current is approximately 20-25 mA, making the total board consumption just under 100 mA. 
The schematic diagram of the module is shown below:

Specifications

– Dimensions: 2.95″ x 0.5″ x 0.125″ (without header pins installed)
– Operating voltage: 3.3-5.0 V
– Supply current: 100 mA
– Output format: 8 analog voltages
– Output voltage range: 0 V to supplied voltage
– Optimal sensing distance: 0.125″ (3 mm)
– Maximum recommended sensing distance: 0.25″ (6 mm)
– Weight without header pins: 0.11 oz (3.09 g)
