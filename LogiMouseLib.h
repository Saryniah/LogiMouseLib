/*
    LogiMouseLib.h - Library extension for USB Host Shield 2.0 Supporting Logitech G502 Mice
    https://github.com/felis/USB_Host_Shield_2.0
    Created by Saryn Niah, October 1, 2022
    Licensed under GNU General Public License.
*/

#ifndef LogiMouseLib_h
    #define LogiMouseLib_h
    #include "Arduino.h"
    #include <hidcomposite.h>
#endif

#define LOGI_LEFT_CLICK 0
#define LOGI_RIGHT_CLICK 1
#define LOGI_MIDDLE_CLICK 2
#define LOGI_SIDE_G5 3
#define LOGI_SIDE_G6 4
#define LOGI_SIDE_G4 5
#define LOGI_SIDE_G7 6
#define LOGI_SIDE_G8 7
#define LOGI_TILT_LEFT 255
#define LOGI_TILT_RIGHT 1
#define LOGI_SCROLL_DOWN -1
#define LOGI_SCROLL_UP 1


class LogiHIDSelector : public HIDComposite{
    public:
        LogiHIDSelector(USB *p);
    protected:
        virtual bool SelectInterface(uint8_t iface, uint8_t proto);
};

class LogiMouseParser : public HIDReportParser{
    uint8_t _sideButtons;
    uint8_t _newButtons;
    bool _buttonArr[8] = {0};
    uint8_t _xbrute;
    uint8_t _ybrute;
    int8_t _xm;
    int8_t _ym;
    uint8_t _scr;
    uint8_t _tilt;
    public:
        LogiMouseParser();
        virtual void Parse(USBHID *hid, bool is_prt_id, uint8_t len, uint8_t *buf);
        virtual bool readButton(uint8_t button_id);
        virtual uint8_t readTilt();
        virtual int8_t readMouseX();
        virtual int8_t readMouseY();
        virtual int8_t readScroll();
};

