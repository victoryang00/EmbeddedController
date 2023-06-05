#include <iostream>
#include <windows.h>

#include "ec.hpp"

unsigned short read16(EmbeddedController f, unsigned char offset)
{
    unsigned short s = f.readDword(offset);
    return s;
}

unsigned char read8(EmbeddedController f, unsigned char offset)
{
    unsigned char c = f.readWord(offset);
    return c;
}

unsigned char read1(EmbeddedController f, unsigned char offset, unsigned char bit)
{
    unsigned char c = f.readByte(offset);
    return (c & (1 << bit)) > 0 ? 1 : 0;
}

void write8(EmbeddedController f, unsigned char offset, const unsigned char value)
{
    unsigned char c = f.readWord(offset);
    f.writeWord(offset, value);
}

void write1(EmbeddedController f, unsigned char offset, unsigned char bit, const unsigned char value)
{
    unsigned char c = read8(f, offset);
    if (value > 0)
    {
        c |= (1 << bit);
    }
    else
    {
        c &= ~(1 << bit);
    }
    f.writeByte(offset,c);
}

int main()
{
    EmbeddedController ec = EmbeddedController();

    // Making sure driver file loaded successfully
    if (ec.driverFileExist && ec.driverLoaded)
    {
        //  commented-out values are from an older Gigabyte model; not all of these seem to be valid for the Aero 15
        //    printf("  USB Charge During Sleep              [0x01.5]: %d\n", read1(ec, 0x01, 5));
        //    printf("  USB Charge During Hibernate          [0x07.2]: %d\n", read1(ec, 0x07, 2));
        //    printf("  Camera Enabled                         [0x01.6]: %d\n", read1(ec, 0x01, 6));
        //    printf("  Bluetooth Enabled                      [0x01.7]: %d\n", read1(ec, 0x01, 7));
        //    printf("  WiFi Enabled                           [0x02.6]: %d\n", read1(ec, 0x02, 6));
        //    printf("  Touchpad Enabled                       [0x03.5]: %d\n", read1(ec, 0x03, 5));
        //    printf("  Ambient Light                        [0x66]:   %d%%\n", read8(ec, 0x66));
        //    printf("  Screen Disabled                        [0x09.3]: %d\n", read1(ec, 0x09, 3));
        //    printf("  Keyboard Backlight Mode                [0xD7]:   %d\n", read8(ec, 0xD7));
        printf("  CPU Temp                               [0x60]:   %d C\n", read8(ec, 0x60));
        printf("  GPU Temp                               [0x61]:   %d C\n", read8(ec, 0x61));
        printf("  MLB Temp                               [0x62]:   %d C\n", read8(ec, 0x62));
        printf("  Fan0 Speed                             [0xFC]:   %d RPM\n", read16(ec, 0xFC));
        printf("  Fan1 Speed                             [0xFE]:   %d RPM\n", read16(ec, 0xFE));
        printf("  Fan Control Enabled                    [0x13.3]: %d\n", read1(ec, 0x13, 3));
        printf("  Fan Quiet Mode Enabled                 [0x08.6]: %d\n", read1(ec, 0x08, 6));
        printf("  Fan Gaming Mode Enabled                [0x0C.4]: %d\n", read1(ec, 0x0C, 4));
        printf("  Fan Custom Mode Enabled                [0x0D.7]: %d\n", read1(ec, 0x0D, 7));
        printf("  Fan Custom Mode - Fixed Speed          [0x06.4]: %d\n", read1(ec, 0x06, 4)); // untested
        printf("  Fan0 Custom Speed Setting              [0xB0]:   %d%%\n", (int)round(read8(ec, 0xB0) / 2.55));
        printf("  Fan1 Custom Speed Setting              [0xB1]:   %d%%\n", (int)round(read8(ec, 0xB1) / 2.55));
        //    printf("  Current Speed Setting                [0x64]:   %d\n", read8(ec, 0x64));

        // register 0f: 01110000 on standard, 01110100 on custom
        printf("  Special Charge Modes (express/custom)  [0x0F.2]: %d\n", read1(ec, 0x0F, 2));
        printf("  Custom Charge Mode                     [0xC6.0]: %d\n", read1(ec, 0xC6, 0));
        printf("  Max. Charge Percentage                 [0xA9]:   %d%%\n", read8(ec, 0xA9));

        auto value = ec.readByte(0x01);
        // Free up the resources at the end
        ec.writeByte(0x01, 0xe3);
        ec.close();
    } else{
        printf("  Driver not loaded\n");
    }
}