#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

const byte pltUhf1FunctionPins[4] = {2, 3, 4, 5};
const byte pltUhf1FreqModePins[3] = {6, 7, 8};
const byte pltUhf1PresetsDecPin = 9;
const byte pltUhf1PresetsIncPin = 10;
const byte pltUhf1VolPin = A1;
const byte pltUhf1BrightnessPin = A2;

// A custom rotary encoder with four quadrature steps per physical detent.
typedef DcsBios::RotaryEncoderT<POLL_EVERY_TIME, DcsBios::FOUR_STEPS_PER_DETENT> FourStepRotaryEncoder; 

DcsBios::SwitchMultiPos pltUhf1Function("PLT_UHF1_FUNCTION", pltUhf1FunctionPins, 4);
DcsBios::SwitchMultiPos pltUhf1FreqMode("PLT_UHF1_FREQ_MODE", pltUhf1FreqModePins, 3);
FourStepRotaryEncoder pltUhf1Presets("PLT_UHF1_PRESETS", "DEC", "INC", pltUhf1PresetsDecPin, pltUhf1PresetsIncPin);
DcsBios::Potentiometer pltUhf1Vol("PLT_UHF1_VOL", pltUhf1VolPin);
DcsBios::Potentiometer pltUhf1Brightness("PLT_UHF1_BRIGHTNESS", pltUhf1BrightnessPin);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
