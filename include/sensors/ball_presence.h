#pragma once

#define BALL_PRESENCE_THRESHOLD 150

class BallPresence {
private:
    int p_value{0}, value{0};
public:
    bool present{false};

    BallPresence();
    void update();
};
