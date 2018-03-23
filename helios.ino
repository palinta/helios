#include "helios.h"

void setup() {
    // publish particle functions
    Particle.function("relayOn", relayOn);
    Particle.function("relayOff", relayOff);
    Particle.function("switchRState", switchRelayState);
    Particle.function("eLikeABoss", enterLikeABoss);

    client.connect("palinta-client");
    if (client.isConnected()) {
        client.subscribe(RELAY_MQTT_TOPIC);
    }
}

void loop() {
    if (client.isConnected()) {
        client.loop();
    } else {
        client.connect("palinta-client");
        if (client.isConnected()) {
            client.subscribe(RELAY_MQTT_TOPIC);
        }
    }
}

int relayOn(String command) {
  if (!relay.isRelayOn()) {
      relay.on();
  }
  Particle.publish(RELAY_STATE, "true");
  return 1;
}

int relayOff(String command) {
  if (relay.isRelayOn()) {
      relay.off();
  }
  Particle.publish(RELAY_STATE, "false");
  return 1;
}

int switchRelayState(String command) {
    if (relay.isRelayOn ()) {
        return relayOff (command);
    } else {
        return relayOn (command);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    if (!strcmp(p, "On"))
        relayOn ("mqtt");
    else if (!strcmp(p, "Off"))
        relayOff ("mqtt");
    delay(1000);
}

int enterLikeABoss(String command) {
    if (command == "start") {
        client.publish("palinta/startEnteringLikeABoss", "");
        relayOn ("");
    } else {
        client.publish("palinta/stopEnteringLikeABoss", "");
        relayOff ("");
    }
    client.publish("palinta/enterLikeABoss", command);
    return 1;
}
