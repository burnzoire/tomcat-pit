//#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_IRQ_SERIAL

#include <TM1637TinyDisplay6.h>
#include <DcsBios.h>

#define CLK 24
#define DIO 25


const byte pltUhf1FunctionPins[4] = {2, 3, 4, 5};
const byte pltUhf1FreqModePins[3] = {6, 7, 8};
const byte pltUhf1PresetsDecPin = 9;
const byte pltUhf1PresetsIncPin = 10;
const byte pltUhf1LoadPin = 11;
const byte pltUhfTonePin = 12;
const byte pltUhf1SquelchPin = 13;
const byte pltUhf1VolPin = A1;
const byte pltUhf1BrightnessPin = A2;
const byte pltUhf101DialPinA = 14;
const byte pltUhf101DialPinB = 15;
const byte pltUhf1025DialPinA = 16;
const byte pltUhf1025DialPinB = 17;
const byte pltUhf1110DialPinA = 18;
const byte pltUhf1110DialPinB = 19;
const byte pltUhf11DialPinA = 20;
const byte pltUhf11DialPinB = 21;
const byte pltUhf1ShowPresetFreqPin = 22;

TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class

// A custom rotary encoder with four quadrature steps per physical detent.
typedef DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::FOUR_STEPS_PER_DETENT> FourStepRotaryEncoder; 

DcsBios::SwitchMultiPos pltUhf1Function("PLT_UHF1_FUNCTION", pltUhf1FunctionPins, 4);
DcsBios::SwitchMultiPos pltUhf1FreqMode("PLT_UHF1_FREQ_MODE", pltUhf1FreqModePins, 3);
FourStepRotaryEncoder pltUhf1Presets("PLT_UHF1_PRESETS", "DEC", "INC", pltUhf1PresetsDecPin, pltUhf1PresetsIncPin);
DcsBios::Potentiometer pltUhf1Vol("PLT_UHF1_VOL", pltUhf1VolPin);
DcsBios::Potentiometer pltUhf1Brightness("PLT_UHF1_BRIGHTNESS", pltUhf1BrightnessPin);
DcsBios::ActionButton pltUhf1LoadToggle("PLT_UHF1_LOAD", "TOGGLE", pltUhf1LoadPin);
DcsBios::ActionButton pltUhf1ToneToggle("PLT_UHF1_TONE", "TOGGLE", pltUhfTonePin);
DcsBios::Switch2Pos pltUhf1Squelch("PLT_UHF1_SQUELCH", pltUhf1SquelchPin);
DcsBios::Switch3Pos pltUhf101Dial("PLT_UHF1_01_DIAL", pltUhf101DialPinA, pltUhf101DialPinB);
DcsBios::Switch3Pos pltUhf1025Dial("PLT_UHF1_025_DIAL", pltUhf1025DialPinA, pltUhf1025DialPinB);
DcsBios::Switch3Pos pltUhf1110Dial("PLT_UHF1_110_DIAL", pltUhf1110DialPinA, pltUhf1110DialPinB);
DcsBios::Switch3Pos pltUhf11Dial("PLT_UHF1_1_DIAL", pltUhf11DialPinA, pltUhf11DialPinB);
DcsBios::Switch2Pos pltUhf1ShowPresetFreq("PLT_UHF1_SHOW_PRESET_FREQ", pltUhf1ShowPresetFreqPin);

int functionPos = 0;
int modePos = 0;
int preset = 1;
String uhfFrequency = "251.000"; 
const byte BRIGHTNESS_HIGH = 7;

// read UHF Function Dial OFF/MAIN/BOTH/ADF
void onPltUhf1FunctionChange(unsigned int newValue) {
    functionPos = newValue;
}
DcsBios::IntegerBuffer pltUhf1FunctionBuffer(0x123e, 0x0c00, 10, onPltUhf1FunctionChange);

// read Frequency Mode Dial MNL/PRESET/GRD
void onPltUhf1FreqModeChange(unsigned int newValue) {
  if(modePos != newValue){
    display.clear();
    modePos = newValue;
  }
}
DcsBios::IntegerBuffer pltUhf1FreqModeBuffer(0x123e, 0x0300, 8, onPltUhf1FreqModeChange);

void onPltUhfRemoteDispChange(char* newValue) {
    uhfFrequency = newValue;
}
DcsBios::StringBuffer<7> pltUhfRemoteDispBuffer(0x1472, onPltUhfRemoteDispChange);

void onPltUhf1BrightnessChange(unsigned int newValue) {
    long brightness = map(long(newValue), 0, 65535, -1, BRIGHTNESS_HIGH);
    bool on = (brightness >= 0);
    display.setBrightness(brightness, on);
}
DcsBios::IntegerBuffer pltUhf1BrightnessBuffer(0x1246, 0xffff, 0, onPltUhf1BrightnessChange);

void setup()
{
  DcsBios::setup();
  
  // animated test sequence
  display.setBrightness(BRIGHTNESS_HIGH);
  display.showString(" F-14 ");
  delay(2500);
  display.showString("UHF-1 ");
  delay(1500);
  display.clear();
  
} 

void loop() {
  DcsBios::loop();
  if(functionPos == 0) {
    display.clear();
  }
  else if(modePos == 0) {
    showUhfPreset();
  }
  else {
    showUhfFrequency();
  }
}

void showUhfPreset(){
  int digit1 = String(uhfFrequency[3]).toInt();
  int digit2 = String(uhfFrequency[4]).toInt();
  int preset = digit1 * 10 + digit2;
  display.showNumber(preset, false, 2, 3);
}

void showUhfFrequency()
{
  // convert freq string to display the colon after the third digit
  int digit1 = String(uhfFrequency[0]).toInt();
  int digit2 = String(uhfFrequency[1]).toInt(); 
  int digit3 = String(uhfFrequency[2]).toInt();
  int digit4 = String(uhfFrequency[4]).toInt();
  int digit5 = String(uhfFrequency[5]).toInt();
  int digit6 = String(uhfFrequency[6]).toInt();
  
  // display the above variables
  display.showNumber(digit1, false, 1, 0);  //  digit1
  display.showNumber(digit2, false, 1, 1);  // digit2
  display.showNumberDec(digit3, 0b10000000, false, 1, 2);  // digit3 with decimal point
  display.showNumber(digit4, false, 1, 3);  // digit4
  display.showNumber(digit5, false, 1, 4);  // digit5
  display.showNumber(digit6, false, 1, 5);  // digit6
}
