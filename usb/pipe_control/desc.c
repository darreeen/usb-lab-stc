#include "desc.h"

// multi-bytes fields store bytes in little endian

/**
*	about string descriptor index:
*		string descriptor contains unicode textual information.
*		each string descriptor has an index for "Get Descriptor(String)" request, host need the index to request string
*		there are index allocated for specific string. index 0x00 is for LANGID, 0x01 for manufacturer, 0x02 for product name, 0x03 for serial number
*/

__code char desc_device[18] = {
	0x12,		// 0.bLength: descriptor size in bytes
				// 			use 0x12 for dec 18 = 0x12 hex
	0x00,		// 1.bDescriptorType:
				//			use 0x1 for DEVICE Descriptor 
	0x00, 0x02, // 2.bcdUSB:	2 Bytes. USB specification release number(BCD)
				//			use 0x0200 because device supports usb full speed(2.0), and it's little endian
	0x00,		// 4.bDeviceClass: device class code.
				//			https://www.usb.org/defined-class-codes
				// 			hid device specify it's class in interface descriptor, and no need for interface association, so use value 0x00
				//			use 0x00.
	0x00,		// 5.bDeviceSubclass: specify subclass within a class
				//			use 0x00 because if the bDeviceClass is 0, then bDeviceSubclass must be 0x00
	0x00,		// 6.bDeviceProtocol: specify protocol for selected class and subclass
				//			use 0x00 for the field is defined by the device's class
	0x00,		// 7.bMaxPacketSize0: max packet size for endpoint 0
				//			use 0x40 (dec 64) for full speed usb support 64
	0xbf, 0x34,	// 8.idVendor: 2 Bytes. vendor id
				//			use 0x34bf for STC chip.
	0x03, 0xff,	// 10.idProduct: 2 Bytes, product id
				//			use 0xff03 for the product id in demo code
	0x00, 0x01,	// 12.bcdDevice: 2 Bytes, device release number(bcd)
				// 			use 0x0100 for device release 1.00
	0x01,		// 14.iManufacturer: index of string descriptor for the manufacturer
				//			the index is the lower byte of wValue. index 0 for requesting language ids, index 1 for manufaccturer string. 2 is for product string
				// 			use 0x1 for manufacturer string
	0x02,		// 15.iProduct: index of string descriptor for the product
				//			using 0x2 for product string
	0x00,		// 16.iSerialNumber: index of string descriptor for serial number
				//			using 0x00 for there's no serial number(??? the book "usb complete" wrote about that but device must NOT return langID according to usb 2.0 spec)
	0x01		// 17.bNumConfigurations: number of possible configurations
				// 			equals the number of configurations the device support at the current operating speed 
				//			using 0x1 as we only has 1 configuration descriptor
};

__code char desc_conf[41] = {
	// configuration descriptor
	0x09,		// 0.bLength: descriptor size in bytes
				// 			use 0x09 
	0x02,		// 1.bDescriptorType
				//			use 0x02 for configuration descriptor
	0x29, 0x00,	// 2.wTotalLength: 2 bytes. number of bytes in the configuration descriptor and all of it's subordinate descriptors.
				//			use 0x0029 (41 dec) for 9(config) + 9(internface) + 9(hid) + 7(endpoint IN) + 7(endpoint OUT)
	0x01,		// 4.bNumInterfaces: number of interfaces in the configuration
				//			use 0x01 for 1 interface
	0x01,		// 5.bConfigurationValue: identifier for Set Configuration and Get Configuration requests for host to specify configuration
				//			use 0x01
	0x00,		// 6.iConfiguration: index of string descriptor for the configuration
				// 			use 0x00, since there's no string descriptor for this configureation
	0x80,		// 7.bmAttributes: self/bus power and remote wakeup settings
				//			use 0x80 for bus powered device and keep compatibility with usb 1.0
	0x32,		// 8.bMaxPower: bus power required in units of 2ma(usb2.0)
				//			use 0x32 (dec 50) for 100ma
				
	// subordinate descriptors:
	// 1. interface descriptor
	//		many of those fields won't be found in common books.
	0x09,		// 0.bLength
	0x04,		// 1.bDescriptorType. use 0x04 for interface descriptor
	0x00,		// 2.bInterfaceNumber: number identifying this interface. this should be zero based, and incremented once for each new interface descriptor
	0x00,		// 3.bAlternativeSetting: identify a descriptor with alternative setting for this bInterfaceNumber
	0x02,		// 4.bNumEndpoints: number of endpoints supported not counting endpoint zero
				//			interface provide functions and it's endpoints provides streams of i/o
				// 			use 0x02. because of endpoint 1 out and endpoint 1 in
	0x03,		// 5.bInterfaceClass: class code.
				// 			use 0x03 for interface descriptor
	0x01,		// 6.bInterfaceSubClass: subclass code
				//			https://en.wikipedia.org/wiki/USB_human_interface_device_class
				//			the sub class code for hid device is used to declare a device bootable. if a device bootable, it could be recognized by BIOS.
				//			use 0x01 for the device is bootable
	0x01,		// 7.bInterfaceProtocol: protocol code
				//			use 0x01 for keyboard protocol
	0x00,		// 8.iInterface: Index of string descriptor for the interface
				//			use 0x00 because there's no string descriptor for this 
	
	// 2. hid class device descriptor
	0x09,		// 0.bLength
	0x21,		// 1.bDescriptorType, use 0x21 for hid
	0x01, 0x01,	// 2.bcdHID: 2 bytes. hid class specification release
				// 			use 0x01, 0x01 for specification 0x101
	0x33,		// 4.bCountryCode: identifying country code of localized hardware
				//			use 0x33, for US Keyboard
	0x01,		// 5.bNumDescriptors: specify the number of class descriptors
				//			report descriptor is hid class specific descriptor, each hid interface at least has 1 report descriptor
				//			use 0x01
	0x22,		// 6.bDescriptorType: constant name identifying type of class descriptor
				//			use 0x22, for hid report descriptor
	0x41, 0x00,	// 7.wDescriptorLength: total size of report descriptor
				// 			use 0x3f or 0x41
	
	// 3. endpoint in descriptor
	0x07,		// 0.bLength
	0x05,		// 1.bDescriptorType, use 0x05 for endpoint
	0x81,		// 2.bEndpointAddress: endpoint number and direction
				//			bit 0-3 for endpoint number, bit 7 is the direction OUT = 0, IN = 1
				//			use 0x81 for endpoint 1 IN
	0x03,		// 3.bmAttributes: transfer type and supplementary information
				//			bit 1-0 specify transfer type: 0b00 control, 0b01=isochronous, 0b10=bulk, 0b11=interrupt
				//			use 0x03 for interrupt transfer
	0x08, 0x00,	// 4.wMaxPacketSize: 2 bytes. maximum packet size supported
				//			use 0x08 0x00 (hex 0x0008) is enough for hid  
	0x0a,		// 6.bInterval: service interval or NAK rate
				//			service interval for interrupt and isochronous endpoints
				//			host polls the device at regular intervals and data is transmitted each time the host polls the device 
				//			it's called interrupt transfer because it used for getting interrupt data from the device.
				//			use 0x0a for 10ms interval
	
	// 4. endpoint out descriptor
	0x07,		// 0.bLength
	0x05,		// 1.bDescriptorType
	0x01,		// 2.bEndpointAddress
	0x03,		// 3.bmAttribute
	0x01, 0x00,	// 4.wMaxPacketSize
	0x0a		// 6.bInterval
};

// hid class descriptor: the report descriptor
// http://who-t.blogspot.com/2018/12/understanding-hid-report-descriptors.html
// http://embeddedguruji.blogspot.com/2019/04/learning-usb-hid-in-linux-part-5.html
// https://learn.adafruit.com/custom-hid-devices-in-circuitpython/report-descriptors
// http://eleccelerator.com/usbdescreqparser/
// https://github.com/NordicSemiconductor/ble-sdk-arduino/blob/master/libraries/BLE/examples/ble_HID_keyboard_template/USD%20HID%20Report%20Descriptor%20-%20Keyboard.txt
__code char desc_hid_report[23] = {
	// select usage page and keyboard usage
	0x05, 0x01,	// Global: Usage Pages 1 byte 00000101, Generic Desktop Page 0x01,
				// 			use for select General Desktop Page, and concat with keyboard usage
	0x09, 0x06,	// Local: Usage Keyboard 1 byte 00001001, Keyboard 0x06
	
	// Application Collection
	0xa1, 0x01, // Main: Collection 1 byte 10100001, Application 0x01
						// switch to keyboard control page 
		0x05, 0x07,		// Global: Usage Pages 1 byte 00000101, Keyboard Page 0x07
	// Report Byte 0: Report ID
	// Report Byte 1: Modifier Keys
		// modifier keys: variable input 
		// E0: Left Control 
		// E1: Left Shift
		// E2: Left Alt
		// E3: Left GUI
		// E4: Right Control
		// E5: Right Shift
		// E6: Right Alt
		// E7: Right GUI
		0x19, 0xe0,		// Local: Usage Minimum 00011001, minimum usage id 0xe0 (224 LeftControl)
		0x29, 0xe7,		// Local: Usage maximum 00101001, max usage id 0xe7(231 Keyboard Right GUI)
		0x15, 0x00,		// Global: Logic minimum 00010101, min logic value 0 (a button only has 0 and 1)
		0x25, 0x01,		// Global: Logic maximum 00100101, max logic value 1 
		0x75, 0x01,		// Global: Report size 01110101, each report size 1 bit, 0x01
		0x95, 0x08,		// Global: Report count 10010101, has 8 of the field, 0x08
		0x81, 0x02,		// Main: Input(Data, Variable, Absolute) 10000001, 00000010
						// 		Absolute: a button state is not a relative value, it'a absolute value
						//		Variable: it should be variable. rather than an array
						//		Data: indicate the item defining report fields that contain modifiable device data. rather than an static value(i think both of those should work for keyboard)
	// Report Byte 2: Reserved 
		0x95, 0x01,		// Global: Report count 01011111, has 1 of the field, 0x01
		0x75, 0x08,		// Global: Report size 01110101, each report size 8 bit, 0x08
		0x81, 0x01,		// Main: Input(Constant)
	// Report Byte 3 - Byte 9: Rest Key Codes
		// ordinary key codes: array input
		0x95, 0x06,		// Global: Report count 01011111, has 6 of the field, 0x06
		0x75, 0x08,		// Global: Report size 01110101, each report size 8 bit, 0x08
		0x15, 0x00,		// Global: Logic minimum 00010101, min logic value 0
		0x25, 0x65,		// Global: Logic maximum 00100101, max logic value 101 (0x65) because the array has 101 elements.
		0x19, 0x00,		// Local: Usage Minimum 00011001, minimum usage id 0x00 (0 Reserved Key)
		0x29, 0x65,		// Local: Usage maximum 00101001, max usage id 0x65(101 Keyboard Application)
		0x81, 0x00,		// Main: Input(Data, Array)
	// end the collection
	0xc0				// Main End Collection
	
};
// LANGID desc, index 0
__code char desc_lang[4] = {
	0x04, 		// 0.bLength
	0x03,		// 1.bDescriptorType, 0x03 for string type
	0x09, 0x04		// 2.wLANGID, 2 bytes. 0x0409 for English(United States)
	
	
};
// manufact desc, index 1
__code char desc_manufacturer[12] = {
	0x0c, 		// 0.bLength
	0x03,		// 1.bDescriptorType, 0x03 for string type
	// 2. bSTRING	with Unicode UTF-16LE string
	'D', 0,
	'A', 0,
	'R', 0,
	'E', 0,
	'N', 0
};
// product desc
__code char desc_product[30] = {
	0x1e, 		// 0.bLength
	0x03,		// 1.bDescriptorType, 0x03 for string type
	// 2. bSTRING	with Unicode UTF-16LE string
	'D', 0,
	'A', 0,
	'R', 0,
	'E', 0,
	'N', 0,
	' ', 0,
	'H', 0,
	'I', 0,
	'D', 0,
	' ', 0,
	'D', 0,
	'E', 0,
	'M', 0,
	'O', 0
};
// packet 0
__code char packet0[2] = {
	0, 0
};
// packet 1
__code char packet1[2] = {
	1, 0
};