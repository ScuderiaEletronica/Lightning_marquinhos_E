#include <FlexCAN.h>
#include <kinetis_flexcan.h>

FlexCAN CANbus(500000);
static CAN_message_t txmsg,rxmsg;
unsigned int CLT;
unsigned int MAP;
unsigned int RPM;
unsigned int MAT;

//In Setup
void setup() {
  CANbus.begin();
}

void loop() {
    if ( CANbus.read(rxmsg) ) {

        switch (rxmsg.id){
            case 1512:
                MAP=((int16_t((rxmsg.buf[1]) | (rxmsg.buf[0] << 8)))/10);
                RPM=(int16_t((rxmsg.buf[3]) | (rxmsg.buf[2] << 8)));
                CLT=((uint16_t((rxmsg.buf[5]) | (rxmsg.buf[4] << 8)))/10);
            break;
            
            case 1513:
                MAT=((int16_t((rxmsg.buf[5]) | (rxmsg.buf[4] << 8)))/10);
            break;
        }
    }
}
