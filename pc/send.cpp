#include <stdio.h>
#include <string.h>
#include <lusb0_usb.h>
#include <unistd.h>

#define WDG_TIME 2

int main(int argc, char * * argv) {
  struct usb_bus * bus = NULL;
  struct usb_device * digiSpark = NULL;
  struct usb_device * device = NULL;

  printf("Detecting USB devices...\n");

  // Initialize the USB library
  usb_init();

  // Enumerate the USB device tree
  usb_find_busses();
  usb_find_devices();

  // Iterate through attached busses and devices
  bus = usb_get_busses();
  while (bus != NULL) {
    device = bus->devices;
    while (device != NULL) {
      // Check to see if each USB device matches the DigiSpark Vendor and Product IDs
      if ((device->descriptor.idVendor == 0x16c0) && (device->descriptor.idProduct == 0x05df)) {
        printf("Detected DigiSpark... \n");
        digiSpark = device;
      }

      device = device->next;
    }

    bus = bus->next;
  }

  // If a digiSpark was found
  if (digiSpark != NULL) {
    int result = 0;
    int i = 0;
    int stringLength = 0;
    int numInterfaces = 0;
    struct usb_dev_handle * devHandle = NULL;
    struct usb_interface_descriptor * interface = NULL;

    devHandle = usb_open(digiSpark);

    if (devHandle != NULL) {

      numInterfaces = digiSpark->config->bNumInterfaces;
      interface = & (digiSpark->config->interface[0].altsetting[0]);
      printf("Found %i interfaces, using interface %i\n", numInterfaces, interface->bInterfaceNumber);

      while (true) {
        printf("PING\n");
        result = usb_control_msg(devHandle, (0x01 << 5), 0x09, 0, 'a', 0, 0, 1000);
        if (result < 0) {
          printf("Error %i writing to USB device\n", result);
        }
        sleep(WDG_TIME);
      }

      result = usb_release_interface(devHandle, interface->bInterfaceNumber);
      if (result < 0) {
        printf("Error %i releasing Interface 0\n", result);
        return 1;
      }

      usb_close(devHandle);
    }
  } else {
    printf("No Digispark Found");
    return 1;
  }

  return 0;
}