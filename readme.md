# BLE RGB LED
This is a "Hello World" with a CYBLE, specifically a CYBL11573.

Is a GATT server capable of receiving through a characteristic (three-byte array) the RGB values to command an RGB LED. Also has the Device Information service implemented, so that strings can be read. In the advertising mode the LED breathes cyan color, once connected the LED breathes in magenta color until the server receives a value to be written.

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