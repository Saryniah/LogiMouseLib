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
        _sideButtons = 0;
        for(uint8_t i = 0; i < 5; i++){
            butBuf[i] = (buf[3]==30+i);
            _sideButtons |= (butBuf[i]<<i);
        }
    }else{
        _newButtons = (buf[0]);
        _xbrute = buf[2];
        _ybrute = buf[4];
        _scr = buf[6]; //BUG: SCROLL Doesn't send interrupt to demark stopped scrolling, value stays until next interrupt
        _tilt = buf[7];//BUG: TILT Doesn't send interrupt to demark stopped tilting, value stays until next interrupt
        if(_xbrute > 127){ _xm = map(_xbrute, 255,128,-1,-127);}
        else if(_xbrute > 0){ _xm = _xbrute;}
        if(_ybrute > 127){ _ym = map(_ybrute, 255,128,-1,-127);}
        else if(_ybrute > 0){_ym = _ybrute;}
    }
    uint8_t buttons = (_newButtons | (_sideButtons<<3));
    uint8_t i = 7;
    for(uint8_t but_id = 128; but_id >= 1; but_id>>=1){
        if(buttons & but_id){
            _buttonArr[i] = true;
        }else{
            _buttonArr[i] = false;
        }
        i--;
    }
}

bool LogiMouseParser::readButton(uint8_t button_id){
    return _buttonArr[button_id];
}

uint8_t LogiMouseParser::readTilt(){
    return _tilt;
}

int8_t LogiMouseParser::readScroll(){
    if(_scr > 0){
        return _scr==1 ? 1 : -1;
    }else{
        return 0;
    }
}

int8_t LogiMouseParser::readMouseX(){
    return _xm;
}

int8_t LogiMouseParser::readMouseY(){
    return _ym;
}


LogiHIDSelector::LogiHIDSelector(USB *p) : HIDComposite(p){}

bool LogiHIDSelector::SelectInterface(uint8_t iface, uint8_t proto){
    if(proto != 1){
        return true;
    }else{
        return false;
    }
}
