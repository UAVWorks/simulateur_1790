#include "Arduino-joystick.h"

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Joystick_HID_Interface = {
    .Config = {
	.InterfaceNumber              = 0,

	.ReportINEndpointNumber       = JOYSTICK_EPNUM,
	.ReportINEndpointSize         = JOYSTICK_EPSIZE,
	.ReportINEndpointDoubleBank   = false,

	.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
	.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
    },
};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */

/** Circular buffer to hold data from the serial port before it is sent to the host. */
RingBuff_t USARTtoUSB_Buffer;

USB_JoystickReport_Data_t joyReport = {0, 0};

#define LED_ON_TICKS 2000	/* Number of ticks to leave LEDs on */
volatile int led1_ticks = 0;

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    SetupHardware();

    RingBuffer_InitBuffer(&USARTtoUSB_Buffer);

    sei();

    for (;;) {
	HID_Device_USBTask(&Joystick_HID_Interface);
	USB_USBTask();

	/* Turn off the Tx LED when the tick count reaches zero */
	if (led1_ticks) {
	    led1_ticks--;
	    if (led1_ticks == 0) {
		LEDs_TurnOffLEDs(LEDS_LED1);
	    }
	}
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Hardware Initialization */
    Serial_Init(115200, true);
    LEDs_Init();
    USB_Init();

    UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);

    USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
    HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Joystick_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either REPORT_ITEM_TYPE_In or REPORT_ITEM_TYPE_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
    uint8_t* const ReportID,
    const uint8_t ReportType,
    void* ReportData,
    uint16_t* const ReportSize)
{
    USB_JoystickReport_Data_t *reportp = (USB_JoystickReport_Data_t*)ReportData;

    RingBuff_Count_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);

    /* If there's a new report from the Arduino, copy it in and send that.
     * If not then the last report is sent again.
     */
    if (BufferCount >= sizeof(joyReport)) {
	uint8_t ind;
	for (ind=0; ind<sizeof(joyReport); ind++) {
	    ((uint8_t *)&joyReport)[ind] = RingBuffer_Remove(&USARTtoUSB_Buffer);
	}

	LEDs_TurnOnLEDs(LEDS_LED1);
	led1_ticks = LED_ON_TICKS;
    }

    *reportp = joyReport;

    *ReportSize = sizeof(joyReport);
    return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either REPORT_ITEM_TYPE_Out or REPORT_ITEM_TYPE_Feature
 *  \param[in] ReportData  Pointer to a buffer where the created report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    /* Not used but must be present */
}

/** ISR to manage the reception of data from the serial port, placing received bytes into a circular buffer
 *  for later transmission to the host.
 */
ISR(USART1_RX_vect, ISR_BLOCK)
{
    uint8_t ReceivedByte = UDR1;

    if ((USB_DeviceState == DEVICE_STATE_Configured) &&
	    !RingBuffer_IsFull(&USARTtoUSB_Buffer)) {
	RingBuffer_Insert(&USARTtoUSB_Buffer, ReceivedByte);
    }
}
