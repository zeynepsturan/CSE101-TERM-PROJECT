#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <fcntl.h>
#include<time.h>


int main() {

    /*Serial port opening and alligning it's settings */
    const char* port = "\\\\.\\COM3";
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    hSerial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state\n");
        CloseHandle(hSerial);
        return 1;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Error setting serial timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }

    int level=0;
    char charLevel=' ';
    printf("##     WELCOME to CSE101 group 5 project   ## \n## PLEASE SELECT FROM THE FOLLOWING  ##\n## MENU :                            ##\n(1) Level 1\n(2) Level 2\n(3) Level 3\n(4) Level 4\n(5) Level 5\n(0) EXIT\nPLEASE SELECT:");
    //scanf("%d", &level);

    while (1){
        do {
            if (scanf("%d", &level) != 1) { // Kullanýcý sayý dýþýnda bir þey girdi
                printf("Invalid Enter.Please enter a number.\n");
                while (getchar() != '\n'); // Buffer'ý temizle
                continue; // Döngünün baþýna dön
            }

            if (level < 0 || level > 5) {
                printf("The number you entered is not between 0 and 5.\n");
            }
        } while (level < 0 || level > 5);

        //printf("Girdiðiniz sayý: %d\n", level);





        if (level == 1)charLevel = 'a';
        else if (level == 2)charLevel = 'b';
        else if (level == 3)charLevel = 'c';
        else if (level == 4)charLevel = 'd';
        else if (level == 5)charLevel = 'e';
        else if (level == 0)break;
        //printf("%c", charLevel);
        DWORD bytesWritten;
        WriteFile(hSerial, &charLevel, strlen(&charLevel), &bytesWritten, NULL);
    }

}