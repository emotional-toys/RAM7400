## RAM7400

Self-satisfaction storage on the metal. On a breadboard and wired to the ideal-ttl board - A 7400 Quad-NAND into a D-latch to store data.

### Background

Implement [this](https://www.instructables.com/DIY-RAM-for-Your-Micro/) idea to test whether or not this will work in how it is being functionally perceived. A choice lies between TTL and newer CMOS production chips in the model.

#### Using 74HC00 (CMOS)

The 74HC00 is a quad 2-input NAND gate. To create a D-latch, you can use two NAND gates configured as a set-reset latch and additional gates to handle the D input and clock.

1. _Set-Reset Latch_: Use two NAND gates to create a set-reset latch. Connect the outputs of these gates to each other's inputs to form a cross-coupled configuration.
2. _D Input and Clock_: Use additional NAND gates to handle the D input and clock signal. The D input and clock signal are combined to control the set and reset inputs of the latch.
3. _Pull-Up Resistors_: CMOS inputs are high-impedance, so you can leave them floating.

#### Using 74LS00 (TTL)

The 74LS00 is also a quad 2-input NAND gate but operates differently from CMOS. TTL inputs are not truly high-impedance when floating, so pull-up resistors are often necessary.

1. _Set-Reset Latch_: Similar to the CMOS version, use two NAND gates to create a set-reset latch.
2. _D Input and Clock_: Use additional NAND gates to handle the D input and clock signal. The configuration is similar to the CMOS version, but ensure the voltage levels are within the TTL specifications.
3. _Pull-Up Resistors_: TTL inputs should be pulled up to Vcc with resistors (e.g., 1kΩ to 10kΩ) to ensure defined logic levels when the inputs are floating.

#### Key Differences

1. _Power Supply_: Ensure a stable 5V power supply for TTL chips, while CMOS chips can operate over a wider voltage range.
2. _Pull-Up Resistors_: TTL inputs require pull-up resistors, while CMOS inputs can be left floating or use pull-up resistors if needed.
3. _Noise Immunity_: TTL chips have better noise immunity due to their specific voltage thresholds, while CMOS chips can be more susceptible to noise, especially at lower supply voltages.
4. _Speed_: TTL chips are generally faster than CMOS chips, which can be beneficial for high-speed applications.

By following these steps and considerations, you can implement a single D-latch using either a 74HC00 CMOS chip or a 74LS00 TTL chip. The wiring and logic design will differ due to the inherent characteristics of each logic family, but the basic concept of using NAND gates to create a set-reset latch and handle the D input and clock signal remains the same.

### Implementation

One byte of RAM read/writable testing via an (old) Arduino Uno.

![layout](/images/finished-setup.jpg)

Parts required for this feature are:

* 8 74LS00 Quad NAND IC
* 8 4.7k -10k resistors
* 2 0.1uF capacitors
* 8 1N4148 diodes
* A 16cm breadboard with 63 rows
* 8 LEDs
* 8 Resistors (current-limiting for the LEDs)

What is nice about this RAM is that each bit is self-contained on each chip.  This means that 8 chips = 1 byte (8 bits) or 4 chips = 1 nybble. With self contained RAM bits, it is a cleaner test-implementation for one breadboard - line the chips up down the board where the pins are oriented the same way. To implement a single D-latch using either a 74HC00 CMOS chip or a 74LS00 TTL chip, the key differences above is the pull-down resistors and the smoothing capacitor to configure the gates for the TTL. The CMOS does not require these. 

![7400-diagram](/images/RAM7400.png)

Shown here is the basic wiring diagram for each of the chips.  What it does is it turns the chip into a self-contained D-latch; remember that a D-latch consumes four NAND gates, which there are 4 NAND gates per chip. On the wiring diagram, the lines that connect the pins are wires that you need to place on each chip.  You do not need to place wires leading out on the `D`, `CLK`, `Q`, and `NOT Q`. Connect `COMM` and `5V` pins to the rails.

![wiring-block-01](/images/wiring-block-01.jpg)

The RAM layout is done; however, the input cannot be connected to the output, meaning that 8 microcontroller pins to send data to the RAM, and 8 pins to fetch data are required. This is not sustainable; rather, use 8 bidirectional pins to send and receive data via a resistor and a diode.

Add a diode from the `Q` pin (either 10 or 11) to a free row on the breadboard.  The black strip on the diode should be toward the free row pin.  If it is toward the connection to the `Q` pin, it needs to be flipped around.  Connect the diode to the Data input pin (pin 1) using the resistor. Repeat for all 8 chips.

![board-diodes-resistors](/images/board-diodes-resistors.jpg)

The D-latch is a neat device: It can store a bit by only changing when the clock signal is high, then it latches onto a bit. If `Q` is on, it sends a `HIGH` signal to the input of `NOT Q`, turning-off `NOT Q`. This, in turn, sends a `LOW` to the input of `Q`, turning `Q` on - this is how it latches. Note that in less-experimental future versions, a 74HC74 would be considered.

_Scenario_

Assume that `NOT Q` is high. When a `HIGH` signal is sent to the clock and data, a `LOW` signal is sent to `Q` and a high is sent to `NOT Q`. This makes `Q`turn on and `NOT Q` turn off. When the clock is set `LOW`, the data line has no effect, so the circuit latches.

In order to use the same pin to send and receive data, add a resistor and diode between the `Q` and `Data` signals. The diode is needed because the latch can be affected by changes on the `Q` pin and diodes restrict the current direction from `Q` to `Data`. The resistor is needed to limit the current going from `Q` to `Data`; otherwise without it, the latch would malfunction since `Q` would be pulled to ground.

_Using the Arduino as a testing environment_

Use the 8-bit port to connect the data lines to and one more pin as the write enable. Follow the C-code file.

![arduino-io](/images/arduino-io.jpg)

The arduino gives digital output using `digitalWrite()` function and gets digital input through `digitalRead()` function. Using these two functions, it can give output or get input from any one pin - meansat a time it can give output to or take input from single pin only. If anyone wants to interface any 8-bit IO device with arduino, it can not give direct 8-bit digital output to device but instead it has to give output to 8 different pins. The data byte (8-bit) pattern is sent to different pins in form of 1’s and 0’s.for example if data byte is `37h` (`0011 0111`) one has to send these `0 n 1` pattern to 8 different pins using digitalWrite() function. So to overcome this situation the project leverages an 8-bit IO Port (input-output port) library for arduino. Using this library one can send direct 8-bit data to any arduino board pins configured as a combined 8-bit port or can get 8-bit input from these configured pins. This library clubs any 8 pins of arduino together to work as 8-bit IO port. Just one has to select any 8 arduino pins to be combined as 8-bit port and it has to configure its data direction as input or output. Data direction is set by character ‘O’ for output or ‘I’ for input.

