 #include <SPI.h>
    #include <MySensor.h>

    #define RADIO_ID 2

    #define WATER_LEAK_SENSOR_DIGITAL_PIN 6
    #define HOT_WATER_SENSOR_DIGITAL_PIN 4
    #define COLD_WATER_SENSOR_DIGITAL_PIN 3
    #define PULSE_FACTOR 1000                       // Nummber of blinks per m3 of your meter (One rotation/liter)
    #define CHILD_ID_HOT_WATER 5
    #define CHILD_ID_COLD_WATER 4                   // Id of the sensor child
    #define CHILD_ID_WATER_LEAK 2
    unsigned long SEND_FREQUENCY = 20;              // Minimum time between send (in seconds). We don't want to spam the gateway.

    MySensor gw;

    double ppl = ((double)PULSE_FACTOR) / 1000;      // Pulses per liter

    volatile unsigned long pulseCountHot = 0;
    volatile unsigned long pulseCountCold = 0;
    volatile unsigned long lastBlinkHot = 0;
    volatile unsigned long lastBlinkCold = 0;
    volatile double flowHot = 0;
    volatile double flowCold = 0;
    unsigned long oldPulseCountHot = 0;
    unsigned long oldPulseCountCold = 0;
    unsigned long newBlinkHot = 0;
    unsigned long newBlinkCold = 0;
    double oldflowHot = 0;
    double oldflowCold = 0;
    double oldtripped = 0;
    double volumeHot;
    double volumeCold;
    double oldvolumeHot;
    double oldvolumeCold;
    unsigned long lastSendHot;
    unsigned long lastSendCold;
    unsigned long lastPulseHot;
    unsigned long lastPulseCold;
    unsigned long currentTimeHot;
    unsigned long currentTimeCold;
    boolean pcReceivedHot = false;
    boolean pcReceivedCold = false;
    int readingCold;
    int readingHot;

    int lastSensorStateHot = 1;   // the previous reading from the input pin
    int sensorStateHot;             // the current reading from the input pin
    long lastDebounceTimeHot = 0;  // the last time the output pin was toggled
    long debounceDelayHot = 50;    // the debounce time; increase if the output flickers

    int lastSensorStateCold = 1;   // the previous reading from the input pin
    int sensorStateCold;             // the current reading from the input pin
    long lastDebounceTimeCold = 0;  // the last time the output pin was toggled
    long debounceDelayCold = 50;    // the debounce time; increase if the output flickers

    boolean metric;
    MyMessage flowMsgHot(CHILD_ID_HOT_WATER, V_FLOW);
    MyMessage volumeMsgHot(CHILD_ID_HOT_WATER, V_VOLUME);
    MyMessage pcMsgHot(CHILD_ID_HOT_WATER, V_VAR1);

    MyMessage flowMsgCold(CHILD_ID_COLD_WATER, V_FLOW);
    MyMessage volumeMsgCold(CHILD_ID_COLD_WATER, V_VOLUME);
    MyMessage pcMsgCold(CHILD_ID_COLD_WATER, V_VAR1);

    MyMessage msg(CHILD_ID_WATER_LEAK, V_TRIPPED);
    void setup() {

      gw.begin(incomingMessage, RADIO_ID);
        delay(90);
      // Send the sketch version information to the gateway and Controller
      gw.sendSketchInfo("Water Meter", "1.0");
        delay(90);
      // Register this device as Waterflow sensor
      gw.present(CHILD_ID_COLD_WATER, S_WATER);
        delay(90);
      gw.present(CHILD_ID_HOT_WATER, S_WATER);
        delay(90);
      gw.present(CHILD_ID_WATER_LEAK, S_MOTION);
        delay(90);
      // Fetch last known pulse count value from gw
      gw.request(CHILD_ID_COLD_WATER, V_VAR1);
     
      gw.request(CHILD_ID_HOT_WATER, V_VAR1);
        
      lastSendCold  = millis();
      lastSendHot = millis();

      pinMode(COLD_WATER_SENSOR_DIGITAL_PIN, INPUT);
      pinMode(HOT_WATER_SENSOR_DIGITAL_PIN, INPUT);

    }

    void incomingMessage(const MyMessage &message) {

      if (message.type == V_VAR1 && message.sensor == 4 && pcReceivedCold == false) {
        pulseCountCold = oldPulseCountCold = message.getLong();
        Serial.print("Received last pulse count from gw for sensor:");
        Serial.print(message.sensor);
        Serial.print(" pulseCountCold ");
        Serial.println(pulseCountCold);
        pcReceivedCold = true;
        delay(100);
        gw.request(CHILD_ID_HOT_WATER, V_VAR1);
      }
      else if (message.type == V_VAR1 && message.sensor == 5 && pcReceivedHot == false) {
        pulseCountHot = oldPulseCountHot = message.getLong();
        Serial.print("Received last pulse count from gw for sensor:");
        Serial.print(message.sensor);
        Serial.print(" pulseCountHot ");
        Serial.println(pulseCountHot);
        pcReceivedHot = true;
        delay(100);
        gw.request(CHILD_ID_COLD_WATER, V_VAR1);
      }
    }

    void loop() {
      gw.process();

      currentTimeCold = millis();
      bool sendTimeCold = currentTimeCold - lastSendCold > 1000 * SEND_FREQUENCY;
     
      if (pcReceivedCold)  {
      
      readingCold = digitalRead(COLD_WATER_SENSOR_DIGITAL_PIN);
      // If the switch changed, due to noise or pressing:
      if (readingCold != lastSensorStateCold) {
        // reset the debouncing timer
        lastDebounceTimeCold = millis();
      }
      if ((millis() - lastDebounceTimeCold) > debounceDelayCold) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (readingCold != sensorStateCold) {
          sensorStateCold = readingCold;

          // only toggle the LED if the new button state is HIGH
          if (sensorStateCold == 0) {
            pulseCountCold++;
        Serial.print(" pulseCountCold ");
        Serial.println(pulseCountCold);
            unsigned long newBlinkCold = micros();
            unsigned long intervalCold = newBlinkCold - lastBlinkCold;
            lastPulseCold = millis();

            flowCold = (60000000.0 / intervalCold) / ppl;
            lastBlinkCold = newBlinkCold;

            Serial.print("flowCold");
            Serial.println(flowCold);
          }
        }

      }
      }else if (sendTimeCold) {
       // No count received. Try requesting it again
        gw.request(CHILD_ID_COLD_WATER, V_VAR1);
      }
      
      currentTimeHot = millis();  
      bool sendTimeHot = currentTimeHot - lastSendHot > 1000 * SEND_FREQUENCY;
      
    if (pcReceivedHot)  {
      readingHot = digitalRead(HOT_WATER_SENSOR_DIGITAL_PIN);
      // If the switch changed, due to noise or pressing:
      if (readingHot != lastSensorStateHot) {
        // reset the debouncing timer
        lastDebounceTimeHot = millis();
      }
      if ((millis() - lastDebounceTimeHot) > debounceDelayHot) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (readingHot != sensorStateHot) {
          sensorStateHot = readingHot;

          // only toggle the LED if the new button state is HIGH
          if (sensorStateHot == 0) {
            pulseCountHot++;
        Serial.print(" pulseCountHot ");
        Serial.println(pulseCountHot);
            unsigned long newBlinkHot = micros();
            unsigned long intervalHot = newBlinkHot - lastBlinkHot;
            lastPulseHot = millis();

            flowHot = (60000000.0 / intervalHot) / ppl;
            lastBlinkHot = newBlinkHot;

            Serial.print("flowHot");
            Serial.println(flowHot);
          }
        }

      }
      }else if (currentTimeHot) {
       // No count received. Try requesting it again
        gw.request(CHILD_ID_HOT_WATER, V_VAR1);
      }
      
        // Only send values at a maximum frequency
      if (pcReceivedCold && sendTimeCold)  {

        // No Pulse count in 2min reset flow
      if (currentTimeCold - lastPulseCold > 120000) {
        flowCold = 0;
        if (flowCold != oldflowCold) {
          gw.send(flowMsgCold.set(flowCold, 2));                   // Send flow value to gw
          oldflowCold = flowCold;
          Serial.println("flowCold Reset");
        }
      }
        // Pulse count has changed
        if (pulseCountCold != oldPulseCountCold) {
          gw.send(pcMsgCold.set(pulseCountCold));                  // Send  volumevalue to gw VAR1
          double volumeCold = ((double)pulseCountCold / ((double)PULSE_FACTOR));
          oldPulseCountCold = pulseCountCold;
          Serial.print("PulseCold count:");
          Serial.println(pulseCountCold);
          if (volumeCold != oldvolumeCold) {
            gw.send(volumeMsgCold.set(volumeCold, 3));
            Serial.print("m3Cold:");
            Serial.println(volumeCold, 3);
            oldvolumeCold = volumeCold;
          }
          if (flowCold != oldflowCold) {
            gw.send(flowMsgCold.set(flowCold, 2));
            Serial.print("l/min Cold:");
            Serial.println(flowCold);
            oldflowCold = flowCold;
          }
          lastSendCold = currentTimeCold;
        }  
      }
        
    if  (pcReceivedHot && sendTimeHot) {    

      // No Pulse count in 2min reset flow
      if (currentTimeHot - lastPulseHot > 120000) {
        flowHot = 0;
        if (flowHot != oldflowHot) {
          gw.send(flowMsgHot.set(flowHot, 2));                   // Send flow value to gw
          oldflowHot = flowHot;
          Serial.println("flowHot Reset");
        }
      }
        // Pulse count has changed
        if (pulseCountHot != oldPulseCountHot) {
          gw.send(pcMsgHot.set(pulseCountHot));                  // Send  volumevalue to gw VAR1
          double volumeHot = ((double)pulseCountHot / ((double)PULSE_FACTOR));
          oldPulseCountHot = pulseCountHot;
          Serial.print("PulseHot count:");
          Serial.println(pulseCountHot);
          if (volumeHot != oldvolumeHot) {
            gw.send(volumeMsgHot.set(volumeHot, 3));
            Serial.print("m3Hot:");
            Serial.println(volumeHot, 3);
            oldvolumeHot = volumeHot;
          }
          if (flowHot != oldflowHot) {
            gw.send(flowMsgHot.set(flowHot, 2));
            Serial.print("l/min Hot:");
            Serial.println(flowHot);
            oldflowHot = flowHot;
          }
          lastSendHot = currentTimeHot;
        }

      }

      lastSensorStateCold = readingCold;
      lastSensorStateHot = readingHot;

      boolean tripped = digitalRead(WATER_LEAK_SENSOR_DIGITAL_PIN) == LOW;
      if (tripped != oldtripped) {
        Serial.println(tripped);
        gw.send(msg.set(tripped?"1":"0")); 
        oldtripped = tripped;
      }



    }
