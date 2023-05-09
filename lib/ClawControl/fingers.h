#ifndef FINGERS_H
#define FINGERS_H

class Fingers {
public:
    Fingers(int pin);
    ~Fingers();

    enum State {
        Unknown,
        Open,
        Closed
    }

    void open();
    void close();

private:
    int m_pin
    Fingers::State:: m_state;

    void set_pwm_pin(int pin, void* callback);
};

#endif // FINGERS_H
