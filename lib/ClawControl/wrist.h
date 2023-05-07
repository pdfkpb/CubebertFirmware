#ifndef WRIST_H
#define WRIST_H

#define HOMING_SPEED 0.2

enum Direction {
    CW,
    CCW
};

class Wrist {
public:
    Wrist(int stepPin, int directionPin, int sleepPin, int homingPin);
    ~Wrist();

    void enable();
    void disable();

    void home();
    void turn(int deg);
    void setSpeed(float speed); // [0.0, 1.0)
    void setDirection(Direction direction);

private:
    int m_stepPin;
    int m_directionPin;
    int m_sleepPin;
    int m_homingPin;

    int m_currentAngle;
    int m_angle;
    float m_speed;
    Direction m_direction;
};

#endif // WRIST_H
