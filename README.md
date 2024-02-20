ECE-218 Project 3 02/19/2024
Papa and Max

DESCRIPTION OF SYSTEM BEHAVIOR:
  The Windshield-wiper system, as simulated with an Arm Cortex-M microcontroller, was implemented with various subsystems that represented specific parts of a car. The system will not operate unless the 'engine'--represented by a blue LED--is turned on. The car engine can be turned on if the ignition button (blue button on development board) is pressed while the driver seat occupancy sensor (external push button) is activated. Once the engine is turned on, the user will be able to toggle (using two potentiometers) between various settings that the windshield wiper can be assigned to. The first potentiometer allows the user to choose whether the wiper will be set to OFF, LOW speed, HIGH speed, or INT mode. LOW and HIGH speed activate the wiper (represented by a servo motor) in a repetetive motion with no delay time inbetween each cycle. The OFF mode will not move the wiper unless they were previously moving, in which case they would return to the initial position. Finally, the INT mode, or intermittent mode, sets the wiper to a setting where a delay will occur between each cycle (one up and don motion). The second potentiometer, or the intermittent settings selector, is what changes the delay time for this intermittent mode. The settings can be changed to SHORT, MEDIUM, or LONG (3, 6, and 8 seconds respectively), to increase the delay at which the wiper repeats its cycle. Any time a wiper setting is changed with either of the potentiometers, the current setting will be displayed on an LCD screen for optimal user interface control.

SUMMARY OF TEST RESULTS:

Ignition Subsystem:

Start the engine (i.e., light the blue LED) while the driver’s seat is occupied and when the ignition button is pushed and then released.
PASS: once button is released, while the driver's seat is occupied, the engine  will turn on.

Keep the engine running even if the driver should exit the vehicle.
PASS: if the driver's seat is unoccupied, engine will remain on.

When the engine is running, stop the engine when the ignition button is pushed (i.e., before the button is released).
PASS: ignition button will be able to activate (in association with the driver seat sensor) or deactivate the entire system (engine)

WINDSHIELD WIPER SUBSYSTEM

If the engine is running, and the user selects HI, LO, INT, or OFF, run the wipers in the appropriate mode, with the typical parameter values, as described above. Read the desired delay time for INT mode from the intermittent delay time selector. Do not run the wipers if the engine is not running. display the selected mode, including the delay time selection (SHORT, MEDIUM, or LONG) for intermittent mode.
PASS: any setting the user may choose for their windsheild wipers will be displayed, and wipers are unoperational when the engine is off.

If the wiper mode selector is turned to OFF, or the engine is turned off, then: if the wiper is moving, in any mode, complete the current cycle and return the wipers to 0 degrees; f the wiper is hesitating in INT mode, remain stationary.
PASS: Ignition button or a change in settings will return the windshield wipers to the original position.



