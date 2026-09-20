# MOSFET-Based-Boost-Converter-with-Arduino-PID-Control

This low current BS170 MOSFET based boost converter uses an Arduino Uno R3 running PID controller code, to adjust the PWM output to reach a customisable desired voltage, using a voltage divider to step down the voltage in the feedback loop for the Arduino. The code and the accompanying schematic are set up for a maximum boosted voltage of 50V, however this can be changed in the code and the configuration of the voltage divider circuit. Since using a MOSFET for the switching and the use of several filtering capacitors, the output noise and voltage ripple is minimal, especially considering the source voltage is also from a switching power supply.

Uses the PID_v1 Arduino Library made by Brett Beauregard.

Max Ratings:

Power: 0.5W

Current: 0.5A

Voltage: 50V

Components:

BS170 MOSFET

100uH Inductor

Fast Schottky Diode

1x 0.1uF capacitor

1x 100pF capacitor

1x 10uF capacitor

1x 100uF capacitor

1x 1k Ohm Resistors

1x 220 Ohm resistor

1x 4.7k Ohm resistor

2x 2.2k Ohm resistor
