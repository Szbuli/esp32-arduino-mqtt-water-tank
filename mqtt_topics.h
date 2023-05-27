#define MQTT_STATUS_TOPIC "smarthome/water-tank/status"
#define MQTT_PUMP_TOPIC "smarthome/water-tank/pump/set"
#define MQTT_WATER_LEVEL_TOPIC "smarthome/water-tank/water-level"
#define MQTT_WATER_TEMP_TOPIC "smarthome/water-tank/water/temperature"
#define MQTT_SENSOR_HEIGHT_TOPIC "smarthome/water-tank/water-level/sensor-height"
#define MQTT_MAX_WATER_LEVEL_TOPIC "smarthome/water-tank/water-level/max-water-level"

#define MQTT_HA_DISCOVERY_WATER_TEMP_TOPIC "homeassistant/sensor/water-tank/water-temperature/config"
#define MQTT_HA_DISCOVERY_PUMP_TOPIC "homeassistant/switch/water-tank/pump/config"
#define MQTT_HA_DISCOVERY_WATER_LEVEL_TOPIC "homeassistant/sensor/water-tank/water-level/config"
#define MQTT_HA_DISCOVERY_CONNECTIVITY_TOPIC "homeassistant/binary_sensor/water-tank/status/config"
#define MQTT_HA_DISCOVERY_SENSOR_LEVEL_TOPIC "homeassistant/number/water-tank/water-level-sensor-height/config"
#define MQTT_HA_DISCOVERY_MAX_WATER_LEVEL__TOPIC "homeassistant/number/water-tank/max-water-level/config"

#define ONLINE_PAYLOAD "online"
#define OFFLINE_PAYLOAD "offline"