#include <Arduino.h>
#include <LogiMouseLib.h>

//Create instances for USB, HID Interface Selector, and the Parser
USB Usb;
LogiHIDSelector Hid(&Usb);
LogiMouseParser mouse;

//Variables for button reading
bool leftClick = false;
bool rightClick = false;
bool middleClick = false;
bool sideButtonG5 = false;
bool sideButtonG6 = false;
bool sideButtonG4 = false;
bool sideButtonG7 = false;
bool sideButtonG8 = false;
bool tiltMiddleLeft = false;
bool tiltMiddleRight = false;
bool scrollDown = false;
bool scrollUp = false;
int8_t mouseX = 0;
int8_t mouseY = 0;


void setup()
{
    Serial.begin( 115200 );
    Serial.println("Start");

    //Check if USB started successfully
    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    //Check if HID Report protocol parser was set successfully
    if (!Hid.SetReportParser(0, &mouse))
    ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);

    //Short wait, cause it feels like I should.
    delay( 200 );

}


void loop()
{
  Usb.Task();
  //Read Mouse Inputs
  leftClick = mouse.readButton(LOGI_LEFT_CLICK);
  rightClick = mouse.readButton(LOGI_RIGHT_CLICK);
  middleClick = mouse.readButton(LOGI_MIDDLE_CLICK);
  sideButtonG5 = mouse.readButton(LOGI_SIDE_G5);
  sideButtonG6 = mouse.readButton(LOGI_SIDE_G6);
  sideButtonG4 = mouse.readButton(LOGI_SIDE_G4);
  sideButtonG7 = mouse.readButton(LOGI_SIDE_G7);
  sideButtonG8 = mouse.readButton(LOGI_SIDE_G8);

  mouseX = mouse.readMouseX(); //I am unsure exactly what the numbers are. Specification calls it "X Movement"
  mouseY = mouse.readMouseY(); //I am unsure exactly what the numbers are. Specification calls it "Y Movement"

  if(mouse.readTilt() == LOGI_TILT_LEFT){
    tiltMiddleLeft = true;
  }else{
    tiltMiddleLeft = false;
  }

  if(mouse.readTilt() == LOGI_TILT_RIGHT){
    tiltMiddleRight = true;
  }else{
    tiltMiddleRight = false;
  }

  if(mouse.readScroll() == LOGI_SCROLL_DOWN){
    scrollDown = true;
  }else{
    scrollDown = false;
  }

  if(mouse.readScroll() == LOGI_SCROLL_UP){
    scrollUp = true;
  }else{
    scrollUp = false;
  }

  //Print mouse inputs
  Serial.print("MouseX: ");
  Serial.print(mouseX);
  Serial.print(" , ");
  Serial.print("MouseY: ");
  Serial.print(mouseY);
  Serial.print(" , ");
  Serial.print("Left: ");
  Serial.print(leftClick);
  Serial.print(" , ");
  Serial.print("Right: ");
  Serial.print(rightClick);
  Serial.print(" , ");
  Serial.print("Middle: ");
  Serial.print(middleClick);
  Serial.print(" , ");
  Serial.print("G5: ");
  Serial.print(sideButtonG5);
  Serial.print(" , ");
  Serial.print("G6 (AIM): ");
  Serial.print(sideButtonG6);
  Serial.print(" , ");
  Serial.print("G4: ");
  Serial.print(sideButtonG4);
  Serial.print(" , ");
  Serial.print("G7: ");
  Serial.print(sideButtonG7);
  Serial.print(" , ");
  Serial.print("G8: ");
  Serial.print(sideButtonG8);
  Serial.print(" , ");
  Serial.print("Left Tilt: ");
  Serial.print(tiltMiddleLeft);
  Serial.print(" , ");
  Serial.print("Right Tilt: ");
  Serial.print(tiltMiddleRight);
  Serial.print(" , ");
  Serial.print("Scroll Dn: ");
  Serial.print(scrollDown);
  Serial.print(" , ");
  Serial.print("Scroll Up: ");
  Serial.print(scrollUp);
  Serial.println("\n");
  delay(200);

}




