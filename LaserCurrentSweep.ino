/* Libraries */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_VEML7700.h>

/* Functions */

/* Variables and Objects */

Adafruit_INA219 ina219;
Adafruit_VEML7700 veml = Adafruit_VEML7700();

/* Setup */
void setup() {
  Serial.begin(9600);

  uint32_t currentFrequency;

  ina219.begin();
  ina219.setCalibration_16V_400mA();

    while (!Serial) { delay(10); }
  Serial.begin(115200);
  Serial.println("Adafruit VEML7700 Test");

  if (!veml.begin()) {
    Serial.println("Sensor not found");
    while (1);
  }
  Serial.println("Sensor found");

  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  Serial.print(F("Gain: "));
  switch (veml.getGain()) {
    case VEML7700_GAIN_1: Serial.println("1"); break;
    case VEML7700_GAIN_2: Serial.println("2"); break;
    case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
    case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
  }

  Serial.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime()) {
    case VEML7700_IT_25MS: Serial.println("25"); break;
    case VEML7700_IT_50MS: Serial.println("50"); break;
    case VEML7700_IT_100MS: Serial.println("100"); break;
    case VEML7700_IT_200MS: Serial.println("200"); break;
    case VEML7700_IT_400MS: Serial.println("400"); break;
    case VEML7700_IT_800MS: Serial.println("800"); break;
  }

  //veml.powerSaveEnable(true);
  //veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);

  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);
  Serial.println("A0, Lux, FwdI");
}

/* Loop */
void loop() {
  float fwdI = 0;
  float lux = 0;
  for(int i=1023; i>768; i--){
    analogWrite(A0, i);
    fwdI = ina219.getCurrent_mA();
    lux = veml.readWhite() / 10;
    Serial.print(i);
    Serial.print(", "); 
    Serial.print(lux);
    Serial.print(", ");
    Serial.println(fwdI);
    delay(100);
  };
}
