#include <fbsdk/fbsdk.h>

enum eMessageType
{
    // Driver errors
    eSTATUS_SENSOR_RUNTIME_DLL_MISSING,

    // Sensor errors
    eSTATUS_SENSOR_INITIALIZING,
    eSTATUS_SENSOR_NOTCONNECTED,
    eSTATUS_SENSOR_NOTGENUINE,
    eSTATUS_SENSOR_NOTSUPPORTED,
    eSTATUS_SENSOR_INSUFFICIENTBANDWIDTH,
    eSTATUS_SENSOR_NOTPOWERED,    
    eSTATUS_SENSOR_NOTREADY,
};

class StatusHandle
{
private:
    static StatusHandle *mInstance;
    StatusHandle();

public:
    static StatusHandle* One();
    ~StatusHandle();

public:
    void PopMessage(eMessageType pStatus);
};

