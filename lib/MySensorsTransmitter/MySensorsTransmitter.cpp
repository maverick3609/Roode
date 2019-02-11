#include <MySensorsTransmitter.h>
// MySensors presentation

MySensorsTransmitter::MySensorsTransmitter()
{
    devices.threshold = MyMessage(CHILD_ID_THRESHOLD, V_TEXT);
    devices.peoplecounter = MyMessage(CHILD_ID_PEOPLECOUNTER, V_TEXT);
    devices.info = MyMessage(CHILD_ID_INFO, V_TEXT);
    devices.room_switch = MyMessage(CHILD_ID_ROOM_SWITCH, V_STATUS);
}
void MySensorsTransmitter::presentation()
{
    sendSketchInfo("RooDe", ROODE_VERSION, "Version");
    present(CHILD_ID_ROOM_SWITCH, S_BINARY, "Room switch");
    present(CHILD_ID_PEOPLECOUNTER, S_INFO, "Peoplecounter");
    present(CHILD_ID_INFO, S_INFO, "Info");
    // present(CHILD_ID_MOTION, S_BINARY, "Motion sensor");
    present(CHILD_ID_THRESHOLD, S_INFO, "Threshold");
#ifdef USE_BATTERY
    present(CHILD_ID_BATTERY, S_CUSTOM);
#endif
}

// MySensors send function
int MySensorsTransmitter::transmit(MyMessage &message, int val, const char *text)
{

    if (message.sensor == CHILD_ID_THRESHOLD)
    {
        return send(message.set(text));
    }
    else if (message.sensor == CHILD_ID_PEOPLECOUNTER)
    {
        return send(message.set(val));
    }
    else if (message.sensor == CHILD_ID_INFO)
    {
        return send(message.set(text));
    }
    else if (message.sensor == CHILD_ID_ROOM_SWITCH)
    {
        return send(message.set(val));
    }
    return -1;
}

int MySensorsTransmitter::receive(const MyMessage &message)
{
    if (message.type == V_TEXT)
    {
        // Serial.println("V_TEXT update");
        // Serial.print("MySensor message received:");
        // Serial.println(message.sensor);
        // Serial.println(message.type);
        // Serial.println(message.sender);
        // Serial.println(message.getString());
        const char *newThreshold = message.getString();
        char sub[11];
        strncpy(sub, newThreshold, 11);

        // if (message.sensor == 3 && newThreshold.substring(0, 11) == "recalibrate")
        if (message.sensor == CHILD_ID_THRESHOLD && strcmp(sub, "recalibrate"))
        {
            Serial.println(sub);
            return -1;
        }

        if (message.sensor == CHILD_ID_PEOPLECOUNTER)
        {
            delay(30);
            Serial.println(message.getInt());
            return message.getInt();
        }
    }

    return -2;
}