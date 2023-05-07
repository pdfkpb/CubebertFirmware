#ifndef FINGERS_H
#define FINGERS_H

class Fingers {
public:
    Fingers(int pin);
    ~Fingers();

    void open();
    void close();

private:
    int m_pin
};

#endif // FINGERS_H
