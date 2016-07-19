#include <iostream>
//#include <stdio.h>
//#include <fcntl.h>
#include <unistd.h>
//#include <string>

//#include "rs232.h"
#include "ch_time.h"
#include "serialdevice.h"

using namespace std;

int main()
{
    int fd;
    string device_name = "/dev/ttyUSB0";

    SerialDevice *device;
    device->Init(fd, device_name);

    int return_value = 0;
    string command = "*CLS\n";
    return_value = write(fd, command.c_str(), command.length());
    if (return_value == -1)
    {
        cout << "can not write to device: " << device_name << endl;
        return -1;
    }

    string output_string;
    char* output_value = new char [32];
    int n = 0;
    int n_rocycles = 10;
    string scan_count = "TRIG:COUN ";
    scan_count += to_string(n_rocycles);
    scan_count += "\n";

    command = "ROUT:SCAN (@101,102,103)\n";
    return_value = write(fd, command.c_str(), command.length());
    command = "CONF:VOLT:DC 10,0.000022, (@101,102,103)\n";
    return_value = write(fd, command.c_str(), command.length());
    command = scan_count.c_str();
    return_value = write(fd, command.c_str(), command.length());

    chTimerTimestamp start, stop;
    chTimerGetTime(&start);
    command = "READ?\n";
    return_value = write(fd, command.c_str(), command.length());

    do
    {
        n = read(fd, output_value, 1);
        output_string.append(n, output_value[0]);
    }while (output_string.back() != '\n' && n > 0);

    chTimerGetTime(&stop);
    double time = chTimerElapsedTime(&start, &stop);

    cout << "Output: " << output_string << endl;
    cout << "Time: " << time << "s" << endl;
    return return_value;
}
