#include<mbed.h>
Serial pc(USBTX,USBRX);
DigitalOut greenLed(D12);
DigitalOut redLed(D13);
DigitalIn passwordReset(D11);
BusOut display(D2,D3,D4,D5,D6,D9,D10);  //segments A,B,C,D,E,F,G

const int password=2614395;

void displaySeg()
{
    display=0x5B;wait(1);//2
    display=0x7D;wait(1);//6
    display=0x06;wait(1);//1
    display=0x66;wait(1);//4
    display=0x4F;wait(1);//3
    display=0x6F;wait(1);//9
    display=0x6D;wait(1);//5
    display=0x00;//over
}

int main()
{
	pc.printf("UESTC 2004 2021/22 – Password Security System\n");
    pc.printf("=======================================\n\n");
    while(1)
    {
        int wrongTimes=0;
        int userIn;
        greenLed=redLed=0;
        pc.printf("Please enter the password:      ");
        pc.scanf("%d",&userIn);
        while(userIn!=password)
        {
            redLed=1;
            pc.printf("The password is incorrect, please renter it:      ");
            if(++wrongTimes==3) break;
            pc.scanf("%d",&userIn);   
        }
        if(wrongTimes==3)
        {
            pc.printf("System is locked, please reset!\n");
            while(passwordReset==0);
        }
        else break;
    }
    pc.printf("Correct password\n");
    redLed=0;
    greenLed=1;
    displaySeg();
    return 0;
}