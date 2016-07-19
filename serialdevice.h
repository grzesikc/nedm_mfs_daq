#ifndef SERIALDEVICE_H
#define SERIALDEVICE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <strings.h>
#include <string>
#include <iostream>


/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BAUDRATE B115200
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */


class SerialDevice
{
public:
    SerialDevice();
    int Init(int &fd, std::string device_name);
private:
};

#endif // SERIALDEVICE_H
