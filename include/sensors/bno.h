#include <Adafruit_BNO055.h>

class BNO {
public:
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

    BNO();
    void read();
};
