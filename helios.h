#include "relay-lib.h"
#include "MQTT.h"

const char * RELAY_STATE      = "oly_p_rele";
const char * RELAY_MQTT_TOPIC = "palinta/relay";

const int RELAY_PIN           = D0;

RelayLib relay                = RelayLib(RELAY_PIN);

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("iot.eclipse.org", 1883, callback);

int relayOn(String command);

int relayOff(String command);

int switchRelayState(String command);

int enterLikeABoss(String command);
