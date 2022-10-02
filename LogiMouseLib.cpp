/*
    LogiMouseLib.cpp - Library extension for USB Host Shield 2.0 Supporting Logitech G502 Mice
    https://github.com/felis/USB_Host_Shield_2.0
    Created by Saryn Niah, October 1, 2022
    Licensed under GNU General Public License.
*/

#include "LogiMouseLib.h"
#include <Arduino.h>

LogiMouseParser::LogiMouseParser(){
}

void LogiMouseParser::Parse(USBHID *hid, bool is_prt_id, uint8_t len, uint8_t *buf){
    if(len > 8){ //Side buttons len=9
        bool butBuf[5] = {false};
        sideButtons = 0;
        for(uint8_t i = 0; i < 5; i++){
            butBuf[i] = (buf[3]==30+i);
            sideButtons |= (butBuf[i]<<i);
        }
    }else{
        newButtons = (buf[0]);
        xbrute = buf[2];
        ybrute = buf[4];
        scr = buf[6];
        tilt = buf[7];
        if(xbrute > 127){ xm = map(xbrute, 255,128,-1,-127);}
        else if(xbrute > 0){ xm = xbrute;}
        if(ybrute > 127){ ym = map(ybrute, 255,128,-1,-127);}
        else if(ybrute > 0){ym = ybrute;}
    }
    uint8_t buttons = (newButtons | (sideButtons<<3));
    uint8_t i = 7;
    for(uint8_t but_id = 128; but_id >= 1; but_id>>=1){
        if(buttons & but_id){
            buttonArr[i] = true;
        }else{
            buttonArr[i] = false;
        }
        i--;
    }
}

bool LogiMouseParser::readButton(uint8_t button_id){
    return buttonArr[button_id];
}

uint8_t LogiMouseParser::readTilt(){
    return tilt;
}

int8_t LogiMouseParser::readScroll(){
    if(scr > 0){
        return scr==1 ? 1 : -1;
    }else{
        return 0;
    }
}

int8_t LogiMouseParser::readMouseXVelocity(){
    return xm;
}

int8_t LogiMouseParser::readMouseYVelocity(){
    return ym;
}


LogiHIDSelector::LogiHIDSelector(USB *p) : HIDComposite(p){}

bool LogiHIDSelector::SelectInterface(uint8_t iface, uint8_t proto){
    if(proto != 1){
        return true;
    }else{
        return false;
    }
}
