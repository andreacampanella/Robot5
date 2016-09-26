/*
 * Xbox 360 Wireless Controller for Windows library
 * for mbed USBHost library
 * Copyright (c) 2013 Hiroshi Suga
 *
 * VID=0x045e PID=0x0719
 *
 * Reference:
 *  https://github.com/Grumbel/xboxdrv/blob/master/PROTOCOL
 *  http://tattiebogle.net/index.php/ProjectRoot/Xbox360Controller
 */

#include "USBHostXpad.h"

#if 1 or USBHOST_XPAD

#include "dbg.h"

#define DEVICE_TO_HOST  0x80
#define HOST_TO_DEVICE  0x00

USBHostXpad::USBHostXpad()
{
    host = USBHost::getHostInst();
    init();
}

void USBHostXpad::init() {
    dev_connected = false;
    dev = NULL;
    int_in = NULL;
    int_out = NULL;
    xpad_intf = -1;
    xpad_device_found = false;
    nb_ep = 0;
    dev_type = TYPE_UNKNOWN;
    dev_started = false;
}

bool USBHostXpad::connected()
{
    return dev_connected;
}

bool USBHostXpad::connect()
{

    if (dev_connected) {
        return true;
    }

    for (int i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        if ((dev = host->getDevice(i)) != NULL) {
            
            USB_DBG("Trying to connect MSD device\r\n");
            
            if(host->enumerate(dev, this)) break;

            if (xpad_device_found) {
                int_in = dev->getEndpoint(xpad_intf, INTERRUPT_ENDPOINT, IN);
                int_out = dev->getEndpoint(xpad_intf, INTERRUPT_ENDPOINT, OUT);
                
                if (!int_in || !int_out) continue;

                USB_INFO("New MSD device: VID:%04x PID:%04x [dev: %p - intf: %d]", dev->getVid(), dev->getPid(), dev, xpad_intf);
                dev->setName("XPAD", xpad_intf);
                host->registerDriver(dev, xpad_intf, this, &USBHostXpad::init);
                int_in->attach(this, &USBHostXpad::rxHandler);
                host->interruptRead(dev, int_in, report, int_in->getSize(), false);

                Thread::wait(100);
                led(LED_OFF);
                dev_connected = true;
                return true;
            }

        }
    }
    init();
    return false;
}

void USBHostXpad::rxHandler() {
    int len_listen = int_in->getSize();
    int len = int_in->getLengthTransferred();

/*
    for (int i = 0; i < len_listen; i ++) {
        std::printf(" %02x", report[i]);
    }
    std::printf("\r\n");
*/
    if (dev_type == TYPE_XBOX) {
        parseMessage();
    } else
    if (report[0] == 0x08) {
        if (report[1] == 0x80) {
            // Connection Status Messages
            start();
        } else
        if (report[1] == 0x00) {
            // Disconnected Status Messages
            dev_started = false;
        }
    } else
    if (report[0] == 0x00) {
        if ((report[1] == 0x14) ||
            (report[1] == 0x01 && report[2] == 0x00 && report[3] == 0xf0)) {
            // Event data
            parseMessage();
        } else
        if (report[1] == 0x0f) {
            // On connection
            led(LED1_ON);
            start();
            dev_started = true;
        } else
        if (report[1] == 0x00) {
            if (report[3] == 0x13) {
                // Battery charge level
                battery = report[4];
            } else
            if (report[3] == 0xf0) {
                // Device low power mode (HID updates will stop until controller inputs change)
//                restart();
            }
        } else
        if (report[1] == 0xf8) {
            // Status Messages ?
        }
    } else {
        // Unknown
        USB_INFO("rxHandler len:%d data:%02x %02x %02x %02x", len, report[0], report[1], report[2], report[3]);
    }

    if (dev) {
        host->interruptRead(dev, int_in, report, len_listen, false);
    }
}

/*virtual*/ void USBHostXpad::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for MSD driver
    if (vid == 0x045e && (pid == 0x0202 || pid == 0x0285 || pid == 0x0287 || pid == 0x0289)) {
        dev_type = TYPE_XBOX;
    } else
    if (vid == 0x045e && pid == 0x028e) {
        dev_type = TYPE_XBOX360;
    } else
    if (vid == 0x045e && pid == 0x0719) {
        dev_type = TYPE_XBOX360W;
    }
    else
        if (vid == 0x045e && pid == (uint16_t)0x291) {
            dev_type = TYPE_XBOX360W;
        }
    USB_INFO("setVidPid vid:%04x pid:%04x xbox:%d", vid, pid, dev_type);
}

/*virtual*/ bool USBHostXpad::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    USB_INFO("parseInterface class:%02x subclass:%02x protocol:%02x [nb: %d - intf: %d]", intf_class, intf_subclass, intf_protocol, intf_nb, xpad_intf);
    if ((xpad_intf == -1) && (intf_class == 0x58) && (intf_subclass == 0x42) && (intf_protocol == 0x00)) {
        xpad_intf = intf_nb; // XBOX ?
        return true;
    }
    if ((xpad_intf == -1) && (intf_class == 0xff) && (intf_subclass == 0x5d) && (intf_protocol == 0x81)) {
        xpad_intf = intf_nb; // XBOX360W
        return true;
    }
    return false;
}

/*virtual*/ bool USBHostXpad::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    USB_INFO("useEndpoint nb:%d type:%d dir:%d", intf_nb, type, dir);
    if (intf_nb == xpad_intf) {
        if (type == INTERRUPT_ENDPOINT) {
            nb_ep ++;
            if (nb_ep == 2) {
                xpad_device_found = true;
            }
            return true;
        }
    }
    return false;
}


void USBHostXpad::parseMessage()
{
    uint8_t *data = report;

    switch (dev_type) {
    case TYPE_XBOX:
        buttons = ((uint32_t)report[3] << 8) | report[2];
        if (report[4]) buttons |= XPAD_PAD_A;
        if (report[5]) buttons |= XPAD_PAD_B;
        if (report[6]) buttons |= XPAD_PAD_X;
        if (report[7]) buttons |= XPAD_PAD_Y;
        trigger_l = data[10];
        trigger_r = data[11];

        stick_lx = ((int16_t)report[13] << 8) | report[12];
        stick_ly = ((int16_t)report[15] << 8) | report[14];
        stick_rx = ((int16_t)report[17] << 8) | report[16];
        stick_ry = ((int16_t)report[19] << 8) | report[18];
        break;
    case TYPE_XBOX360W:
        data += 4;
    case TYPE_XBOX360:
        buttons = ((uint32_t)data[3] << 8) | data[2];
        trigger_l = data[4];
        trigger_r = data[5];

        stick_lx = ((int16_t)data[7] << 8) | data[6];
        stick_ly = ((int16_t)data[9] << 8) | data[8];
        stick_rx = ((int16_t)data[11] << 8) | data[10];
        stick_ry = ((int16_t)data[13] << 8) | data[12];
        break;
    default:
        return;
    }

    if (onUpdate) {
        (*onUpdate)(buttons, stick_lx, stick_ly, stick_rx, stick_ry, trigger_l, trigger_r);
    }
}

bool USBHostXpad::restart ()
{
    unsigned char odata[32];
    memset(odata, 0, sizeof(odata));
    odata[0] = 0x08;
    odata[2] = 0x0f;
    odata[3] = 0xc0;
    if (dev) {
        for (int i = 0; i < 4; i ++) {
            host->interruptWrite(dev, int_out, odata, 12);
        }
    }
    return true;
}

int USBHostXpad::read (PAD pad)
{
    switch (pad) {
    case XPAD_BUTTONS:
        return buttons;
    case XPAD_STICK_LX:
        return stick_lx;
    case XPAD_STICK_LY:
        return stick_ly;
    case XPAD_STICK_RX:
        return stick_rx;
    case XPAD_STICK_RY:
        return stick_ry;
    case XPAD_TRIGGER_L:
        return trigger_l;
    case XPAD_TRIGGER_R:
        return trigger_r;
    case XPAD_BATTERY:
        return battery;
    default:
        return (buttons & pad) ? 1 : 0;
    }
}

bool USBHostXpad::start()
{
    unsigned char odata[32];
    memset(odata, 0, sizeof(odata));
    odata[3] = 0x40;
    if (dev) {
        if (host->interruptWrite(dev, int_out, odata, 12) != USB_TYPE_OK) {
            return false;
        }
    }
    return true;
}

bool USBHostXpad::stop()
{
    unsigned char odata[32];
    memset(odata, 0, sizeof(odata));
    odata[2] = 0x08;
    odata[3] = 0xc0;
    if (dev) {
        if (host->interruptWrite(dev, int_out, odata, 12) != USB_TYPE_OK) {
            return false;
        }
    }
    return true;
}

bool USBHostXpad::led(LED cmd)
{
    unsigned char odata[32];
    memset(odata, 0, sizeof(odata));
    switch (dev_type) {
    case TYPE_XBOX:
        return true;
    case TYPE_XBOX360:
        odata[0] = 0x01;
        odata[1] = 0x03;
        odata[2] = cmd;
        break;
    case TYPE_XBOX360W:
        odata[2] = 0x08;
        odata[3] = 0x40 + (cmd % 0x0e);
        break;
    default:
        return false;
    }
    if (dev) {
        if (host->interruptWrite(dev, int_out, odata, 12) != USB_TYPE_OK) {
            return false;
        }
    }
    return true;
}

bool USBHostXpad::rumble(uint8_t large, uint8_t small)
{
    unsigned char odata[32];
    memset(odata, 0, sizeof(odata));
    switch (dev_type) {
    case TYPE_XBOX:
        odata[1] = 0x06;
        odata[3] = small;
        odata[5] = large;
        break;
    case TYPE_XBOX360:
        odata[1] = 0x08;
        odata[3] = large;
        odata[4] = small;
        break;
    case TYPE_XBOX360W:
        odata[1] = 0x01;
        odata[2] = 0x0f;
        odata[3] = 0xc0;
        odata[5] = large;
        odata[6] = small;
        break;
    default:
        return false;
    }
    if (dev) {
        if (host->interruptWrite(dev, int_out, odata, 12) != USB_TYPE_OK) {
            return false;
        }
    }
    return true;
}

#endif

