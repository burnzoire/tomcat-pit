#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

const byte pltAfcsPitchPin = 2;
const byte pltAfcsRollPin = 3;
const byte pltAfcsYawPin = 4;
const byte pltAutopltVectorCarrierPinA = A0;
const byte pltAutopltVectorCarrierPinB = A1;
const byte pltAutopltHdgPinA = A4;
const byte pltAutopltHdgPinB = A5;
const byte pltAutopltAltPin = A3;
const byte pltAutopltEngagePinA = 6;
const byte pltAutopltEngagePinB = 7;

const byte ledPin = 5;


DcsBios::Switch2Pos pltAfcsPitch("PLT_AFCS_PITCH", pltAfcsPitchPin);
DcsBios::Switch2Pos pltAfcsRoll("PLT_AFCS_ROLL", pltAfcsRollPin);
DcsBios::Switch2Pos pltAfcsYaw("PLT_AFCS_YAW", pltAfcsYawPin);

DcsBios::Switch3Pos pltAutopltVectorCarrier("PLT_AUTOPLT_VECTOR_CARRIER", pltAutopltVectorCarrierPinA, pltAutopltVectorCarrierPinB);
DcsBios::Switch2Pos pltAutopltAlt("PLT_AUTOPLT_ALT", pltAutopltAltPin);
DcsBios::Switch3Pos pltAutopltHdg("PLT_AUTOPLT_HDG", pltAutopltHdgPinA, pltAutopltHdgPinB);

DcsBios::RotaryEncoder pltAutopltEngage("PLT_AUTOPLT_ENGAGE", "DEC", "INC", pltAutopltEngagePinA, pltAutopltEngagePinB);

void onPltLightIntentInstrumentChange(unsigned int newValue) {
    int brightness = map(newValue, 0, 8, 0, 255);
    analogWrite(ledPin, brightness);
}
DcsBios::IntegerBuffer pltLightIntentInstrumentBuffer(0x121e, 0x0f00, 8, onPltLightIntentInstrumentChange);

void setup() {
  pinMode(ledPin, OUTPUT); 

  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
