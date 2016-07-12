#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#include "rs232.h"

using namespace std;

int main()
{
    string device_name = "/dev/ttyUSB0";
    int device = open(device_name.c_str(),O_RDWR, O_APPEND);
    if (device == -1)
    {
        cout << "can not open device: " << device_name << endl;
        return -1;
    }

    int return_value = 0;
//    string command = "*IDN?\n";
//    return_value = write(device, command.c_str(), command.length());
//    usleep(100000);
//    command = "*RST\n";
//    return_value = write(device, command.c_str(), command.length());
//    command = "ROUT:SCAN (@101,102,103)\n";

//    usleep(100000);
    string command = "MEAS:VOLT:DC? (@101,102,103)\n";
    string output_string;
    return_value = write(device, command.c_str(), command.length());
    char* output_value = new char [32];
    usleep(200000);
    int n = 0;
//    !!!!!!!!!!!!!!!!!!!!!!!!
//    make sure the values are correctly read out

    do
    {
        n = read(device, output_value, 32);
        output_string.append(n, output_value[0]);
    }while( output_string.back() != '\r' && n > 0);

    cout << "Output: " << output_string << endl;

    if (return_value == -1)
    {
        cout << "can not write to device: " << device_name << endl;
        return -1;
    }
    return return_value;
}
