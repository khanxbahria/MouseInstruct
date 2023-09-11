#include <iostream>
#include <thread>
#include <chrono>

#include "MouseInstruct.h"

using namespace std;

MouseInstruct getMouse() {
    try {
        MouseInstruct mouse = MouseInstruct::getMouse(0x2340, 0x484D);
        cout << "[+] Device found!" << endl;
        return mouse;
    }
    catch (DeviceNotFoundException& e) {
        cout << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    MouseInstruct m = getMouse();
    this_thread::sleep_for(chrono::milliseconds(3000));
    // move cursor to draw a square
    int stepSize = 10;
    int stepTotal = 15*10;
    int sleepDuration = 5;
    m.press();
    for (int i = 0; i < stepTotal; i++) {
        m.move(stepSize, 0);
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    for (int i = 0; i < stepTotal; i++) {
        m.move(0, stepSize);
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    for (int i = 0; i < stepTotal; i++) {
        m.move(-stepSize, 0);
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    for (int i = 0; i < stepTotal; i++) {
        m.move(0, -stepSize);
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    m.release();

    
}