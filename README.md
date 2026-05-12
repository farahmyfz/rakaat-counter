# 🕋 Rakaat Counter (Automatic Prayer Cycle Tracker)

Rakaat Counter is an innovative Arduino-based device designed to help Muslims minimize errors in counting the number of Rakaat (prayer cycles) during Salah. This device acts as a digital *Sutrah* (prayer barrier) that automatically detects prostration (*Sujud*) positions to ensure the worship is performed accurately.

## 🚀 How It Works
1. **Initialization**: Upon startup, the LCD displays an initialization message to ensure all sensors are calibrated and ready.
2. **Sujud Detection**: The ultrasonic sensor measures the distance between the user's head and the floor during prostration. If the distance is less than **10 cm**, the device identifies it as a *Sujud* position.
3. **Logic Flow**: 
   - 2 detected prostrations = 1 Rakaat increment.
   - The current Rakaat count is displayed in real-time on a 16x2 I2C LCD screen.

## 🛠️ Components & Hardware
- **Arduino Nano**: The central processing unit.
- **HC-SR04 Ultrasonic Sensor**: For precision distance detection.
- **16x2 I2C LCD**: For the user interface.
- **Power Source**: Battery-powered with an integrated power switch.
- **Enclosure**: Wood-based chassis functioning as a *Sutrah*.

## 💻 Code Implementation
The code includes a specific logic adjustment where the `sujud` variable is initialized at `-1`. This was implemented to prevent premature rakaat increments during the initial hardware power-up/sensing phase.

```cpp
// Core Logic Snippet
if (distance < 10 && !sujudState) {
    sujud++;
    sujudState = true;
    if (sujud == 2) {
        rakaat++;
        sujud = 0;
    }
} else if (distance >= 10) {
    sujudState = false;
}
