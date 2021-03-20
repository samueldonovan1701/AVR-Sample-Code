# avr-gpio
A simple way to manipulate AVR GPIO pins at the register level

## Usage

To use the library, clone or download the repository into your project folder. After that, you can
```c
#include "avr-gpio/GPIO.h"
```

### Functions

<table>
	<tr>
		<th>Signature</th>
		<th>Valid Input</th>
		<th>Returns</th>
		<th>Description</th>
	</tr>
	<tr>
		<td><code>GPIO GPIO(X, byte)</code></td>
		<td>
			<p><code>X</code> can be any <b>raw letter</b> (not a string) of the ports your board supports</p>
			<p><code>byte</code> is the port's bit number</p>
		</td>
		<td><code>GPIO</code> instance</td>
		<td>A macro for constructing a new <code>GPIO</code> instance</td>
	</tr>
	<tr>
		<td><code>void SetMode(byte)</code></td>
		<td><code>INPUT</code>, <code>OUTPUT</code></td>
		<td></td>
		<td>Sets the pin to be an input or output</td>
	</tr>
	<tr>
		<td><code>void AsInput()</code></td>
		<td></td>
		<td></td>
		<td>Sets the pin to be an input</td>
	</tr>
	<tr>
		<td><code>void AsOutput()</code></td>
		<td></td>
		<td></td>
		<td>Sets the pin to be an output</td>
	</tr>
	<tr>
		<td><code>void Write(byte)</code></td>
		<td><code>HIGH</code>, <code>LOW</code></td>
		<td></td>
		<td>Sets the pin's state (must be in <code>OUTPUT</code> mode)</td>
	</tr>
	<tr>
		<td><code>void Low()</code></td>
		<td></td>
		<td></td>
		<td>Sets the pin's state <code>LOW</code> (must be in <code>OUTPUT</code> mode)</td>
	</tr>
	<tr>
		<td><code>void High()</code></td>
		<td></td>
  <td></td>
		<td>Sets the pin's state <code>HIGH</code> (must be in <code>OUTPUT</code> mode)</td>
	</tr>
	<tr>
		<td><code>void Read()</code></td>
		<td></td>
		<td><code>HIGH</code> or <code>LOW</code></td>
		<td>Reads the pin's state (must be in <code>INPUT</code> mode)</td>
	</tr>
</table>

## Supported Boards
On supported boards, pins are predefined and can be accessed via `GPIOXX` where `XX` is the on-board pin number. For example:
```c
GPIO13.Write(HIGH);
```

Currently, the following boards are supported:
- ATMEGA2560
 
Feel free to contribute your own board's pin definitons. 
 
## Limitations
- Only digital input/output is supported
- Not all boards will have pin definitions, although they can be added manually
- Limited run time resolution options
- Pin mode is not checked before attempting to `Read()` or `Write()`, this is left to the user
