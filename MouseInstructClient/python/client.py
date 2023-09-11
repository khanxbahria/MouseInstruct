import time
import sys

from mouse_instruct import MouseInstruct, DeviceNotFoundError

def getMouse():
    try:
        mouse = MouseInstruct.getMouse(0x2340, 0x484D)
        print("[+] Device found!")
    except DeviceNotFoundError as e:
        print(e)
        sys.exit()
    return mouse

def main():
    m = getMouse()
    time.sleep(5)
    # move cursor to draw a square
    step_size = 5
    step_total = 5*10
    sleep_duration = 0.005
    m.press()
    for _ in range(step_total):
        m.move(step_size, 0)
        time.sleep(sleep_duration)
    for _ in range(step_total):
        m.move(0, step_size)
        time.sleep(sleep_duration)
    for _ in range(step_total):
        m.move(-step_size, 0)
        time.sleep(sleep_duration)
    for _ in range(step_total):
        m.move(0, -step_size)
        time.sleep(sleep_duration)
    m.release()

if __name__ == "__main__":
    main()