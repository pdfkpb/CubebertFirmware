#ifndef FINGERS_H
#define FINGERS_H

class Fingers {
public:
    Fingers(int vertPin, int horPin);
    ~Fingers();

private:
    int m_set1Pin;
    int m_set2Pin;

    int m_state;
};

#endif // FINGERS_H