#ifndef _ARDUINO_KEYBOARD_H_
#define _ARDUINO_KEYBOARD_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "Descriptors.h"

#include "Lib/LightweightRingBuff.h"

#include <LUFA/Version.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Peripheral/Serial.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/USB/Class/CDC.h>

/** Type define for the joystick HID report structure, for creating and sending HID reports to the host PC.
 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
 */
typedef struct {
    int16_t axis[4]; /**< Current absolute position axis 1-6, signed 16-bit integer */
} USB_JoystickReport_Data_t;
		
/* Macros: */
/** LED mask for the library LED driver, to indicate TX activity. */
#define LEDMASK_TX               LEDS_LED1

/** LED mask for the library LED driver, to indicate RX activity. */
#define LEDMASK_RX               LEDS_LED2

/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
#define LEDMASK_ERROR            (LEDS_LED1 | LEDS_LED2)

/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
#define LEDMASK_BUSY             (LEDS_LED1 | LEDS_LED2)		

/* Function Prototypes: */
void SetupHardware(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_UnhandledControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
					 uint8_t* const ReportID,
					 const uint8_t ReportType,
					 void* ReportData,
					 uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
					  const uint8_t ReportID, 
					  const uint8_t ReportType,
					  const void* ReportData,
					  const uint16_t ReportSize);

#endif /* _ARDUINO_KEYBOARD_H_ */
