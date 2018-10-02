# BLE RGB LED
This is a "Hello World" with a CYBLE, specifically a CYBL11573.

Is a GATT server capable of receiving through a characteristic (three-byte array) the RGB values to command an RGB LED. Also has the Device Information service implemented, so those strings can be read. In the advertising mode the LED breathes in cyan color, once connected the LED breathes in magenta color until the server receives a value to be written.

The server has the following services:
* Server
  * Generic Access
    * Device Name
    * Apperance
    * ...
  * Generic Atribbute
    * Service Changed
  * RGB LED (Custom Service)
    * Value
  * Device Information
    * Model Number String
    * Serial Number String
    * Hardware Revision String
    * Firmware Revision String

You can watch a [demo video](https://youtu.be/tJKZ75ehog4 "BLE-RGB-LED demo") at YouTube.

