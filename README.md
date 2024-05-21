A TM4C123GH6PM Launchpad is used to implement this project, as well as an HC-05
Bluetooth module. UART 1 is used on the launchpad to send and receive data from the BT
module. Onboard color LEDs show the current mode of the car.

Operation
The car is operated by sending characters to it through a connected Bluetooth device. Here are
the commands and the associated color for each mode:
• ‘w’ is forward – LED is green
• ‘s’ is backward – LED is blue
• ‘a’ is left turn (forward and backward) – LED is yellow
• ‘d’ is right turn (forward and backward) – LED is purple
• spacebar is stop – LED is off
• ‘e’ is speed up – current LED color is kept
• ‘q’ is slow down – current LED color is kept
