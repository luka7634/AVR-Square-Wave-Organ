# 🎹 Serial-Controlled Musical Organ

[![Platform](https://img.shields.io/badge/platform-AVR-007EC6.svg)](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/avr-mcus)
[![Microcontroller](https://img.shields.io/badge/mcu-ATmega168-orange.svg)](https://www.microchip.com/en-us/product/ATmega168)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

## 📖 Overview

A serial-controlled musical organ implemented on an **ATmega168** microcontroller that converts keyboard input from a serial terminal into musical notes through a piezoelectric buzzer. This project demonstrates real-time USART communication, tone generation using timer compare output, and pre-programmed song playback.

**Key Features:**
- 🎵 Real-time note playback via serial terminal
- 🎹 18-key musical keyboard (2 octaves including sharps)
- 🎼 Pre-programmed songs (Twinkle Little Star, Imperial March)
- ⚡ Adjustable note duration (short/long mode)
- 🔌 Simple hardware requirements (MCU + buzzer + serial adapter)

---

## 🛠️ Hardware Requirements

| Component | Specification | Quantity |
|-----------|--------------|----------|
| Microcontroller | ATmega168 (DIP-28) | 1 |
| Buzzer/Piezo | 5V, 2-5kHz range | 1 |
| Resistor | 220Ω - 1kΩ (current limiting) | 1 |
| Crystal | 16MHz (optional, can use internal) | 1 |
| Capacitors | 22pF (for crystal) | 2 |
| USB-to-Serial | FTDI, CP2102, or CH340 | 1 |
| Power Supply | 5V DC | 1 |
| Breadboard | 400+ points | 1 |
| Jumper Wires | Male-male, male-female | As needed |

### Pin Connections

| Microcontroller Pin | Component | Description |
|--------------------|-----------|-------------|
| PD1 (Pin 3) | USB-to-Serial TX | USART Transmit |
| PD0 (Pin 2) | USB-to-Serial RX | USART Receive |
| PDx (configurable) | Buzzer (+) | PWM/Timer output |
| GND | Buzzer (-) | Ground |
| VCC (Pin 7/20) | +5V | Power |
| GND (Pin 8/22) | GND | Ground |

> **Note:** The buzzer pin is defined in `src/includes/pinDefines.h`. Configure according to your wiring.

---

## 💻 Software Requirements

### Development Tools

| Tool | Version | Purpose |
|------|---------|---------|
| [avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) | 14.2.0+ | Compiler |
| [avr-libc](https://www.nongnu.org/avr-libc/) | 2.0.0+ | AVR C Library |
| [avrdude](https://github.com/avrdudes/avrdude) | 7.0+ | Programming utility |
| [make](https://www.gnu.org/software/make/) | 4.0+ | Build automation |
| [Doxygen](https://www.doxygen.nl/) | 1.9+ | Documentation (optional) |

### Installation (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install gcc-avr avr-libc avrdude make doxygen
```

### Installation (macOS)

```bash
brew install avr-gcc avr-libc avrdude make doxygen
```

### Installation (Windows)

Use [WinAVR](http://winavr.sourceforge.net/) or [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio).

---

## 📂 Project Structure

```
serial-organ/
├── Makefile                 # Build configuration
├── Doxyfile                 # Documentation configuration
├── README.md                # This file
├── src/
│   ├── main.c               # Main program entry point
│   ├── organ.c              # Note generation implementation
│   ├── USART.c              # Serial communication implementation
│   ├── pre_defined_songs.c  # Song implementations
│   ├── includes/
│   │   ├── CPU.h            # CPU configuration (F_CPU, BAUD)
│   │   ├── pinDefines.h     # Pin mappings
│   │   ├── scale16.h        # Musical note frequencies
│   │   ├── organ.h          # Note functions declarations
│   │   ├── USART.h          # Serial functions declarations
│   │   └── pre_defined_songs.h # Song declarations
└── docs/                    # Generated documentation (optional)
```

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/serial-organ.git
cd serial-organ
```

### 2. Configure Pin Mapping

Edit `src/includes/pinDefines.h`:

```c
#define BUZZER_DDR   DDRB
#define BUZZER_PORT  PORTB
#define BUZZER_PIN   PB0    // Change to your pin (PB0-PB7)
```

### 3. Configure CPU Settings

Edit `src/includes/CPU.h` if needed:

```c
#define F_CPU 16000000UL    // 16 MHz clock
#define BAUD 9600UL         // Serial baud rate
```

### 4. Build the Project

```bash
make clean    # Clean previous build
make          # Compile the project
```

Successful build produces:
- `main.elf` - Executable file
- `main.hex` - Intel HEX format (for programming)
- `*.o` - Object files

### 5. Program the Microcontroller

**Using avrdude (USBasp programmer):**
```bash
make flash
```

**Using avrdude (Arduino as ISP):**
```bash
avrdude -c arduino -p m168 -P /dev/ttyUSB0 -b 19200 -U flash:w:main.hex
```

**Using another programmer:**
```bash
avrdude -c usbasp -p m168 -U flash:w:main.hex
```

### 6. Connect Serial Terminal

| Setting | Value |
|---------|-------|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

**Recommended terminals:**
- **Linux:** `screen`, `minicom`, `gtkterm`
- **Windows:** PuTTY, RealTerm, Arduino Serial Monitor
- **macOS:** `screen`, CoolTerm

**Example using screen (Linux/macOS):**
```bash
screen /dev/ttyUSB0 9600
```

---

## 🎮 Usage Guide

### Basic Controls

| Key | Action | Description |
|-----|--------|-------------|
| `a` `s` `d` `f` `g` `h` `j` `k` `l` `;` `'` | White keys | Natural notes (C major scale equivalent) |
| `w` `e` `t` `y` `i` `o` `p` | Black keys | Sharp notes (chromatic scale) |
| `[` | Short mode | Notes last 250ms (faster tempo) |
| `]` | Long mode | Notes last 500ms (slower tempo) |
| `1` | Play Song | Twinkle Twinkle Little Star |
| `2` | Play Song | Imperial March (Star Wars) |

### Musical Note Mapping

```
Keyboard Layout (QWERTY):

    w     e    t    y    i    o   p
   (G#4)(A#4)(C#5)(D#5)(F#5)(G#5)(B5)
    
 a   s   d   f   g   h   j   k   l    ;   '
(G4)(A4)(B4)(C5)(D5)(E5)(F5)(G5)(A5)(A#5)(C6)
```

### Example Session

```
---Serial Organ---
Controls: a-s-d-f-g-h-j-k-l-;-' for white keys
          w-e-t-y-i-o-p for black keys
          1 to play Twinkle Twinkle Little Star
          2 to play Imperial March from Star Wars
          '[' = short note (250ms), ']' = long note (500ms)
Ready!

> a     (plays G4)
> s     (plays A4)
> d     (plays B4)
> [     (switches to short mode - 250ms)
> a     (plays G4, shorter duration)
> 1     (plays Twinkle Twinkle Little Star)
> 2     (plays Imperial March)
```

---

## 🎼 Pre-Programmed Songs

### Twinkle Twinkle Little Star
- **Duration:** ~10-15 seconds
- **Notes:** 42 notes in 6 phrases
- **Key:** C major
- **Structure:** Traditional children's song format (AABB)

### Imperial March (Star Wars)
- **Duration:** ~30 seconds
- **Notes:** 50 notes in 10 musical phrases
- **Key:** E minor
- **Composer:** John Williams
- **Structure:** Intro → Theme A → Theme B → Bridge → Climax → Coda

---

## 🔧 Troubleshooting

### Common Issues and Solutions

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| No sound | Wrong buzzer pin | Check pinDefines.h configuration |
| | Missing current limiting resistor | Add 220Ω-1kΩ resistor in series |
| | Buzzer polarity | Most piezo buzzers are non-polarized |
| Garbled serial output | Baud rate mismatch | Ensure 9600 baud, 8N1 |
| | Incorrect F_CPU | Verify F_CPU=16000000UL in CPU.h |
| No serial communication | Wrong USB port | Check /dev/ttyUSB0 or /dev/ttyACM0 |
| | RX/TX cross connection | Connect TX→RX, RX→TX |
| Compilation errors | Missing avr-gcc | Install development tools |
| | Wrong include paths | Check Makefile INCLUDES variable |
| Makefile errors | Missing dependencies | Install make, avr-gcc, avr-libc |
| Note duration issues | Using songs with hardcoded durations | Note durations are fixed for songs |

### Debug Commands

```bash
# Check USB device
ls -la /dev/ttyUSB* /dev/ttyACM*

# Test serial connection
echo "a" > /dev/ttyUSB0

# Monitor serial with hex dump
stty -F /dev/ttyUSB0 9600 raw -echo
cat /dev/ttyUSB0 | xxd
```

---

## 📊 Performance Metrics

| Metric | Value |
|--------|-------|
| Flash Usage | ~5.7 KiB (~35% of 16KB) |
| CPU Frequency | 16 MHz |
| Note Latency | 1-2 ms |
| Max Polyphony | 1 (monophonic) |
| Frequency Range | 131 Hz - 1047 Hz (C3 to C6) |
| Buzzer Output | Square wave (50% duty cycle) |

---

## 📚 Documentation

Open  in your browser.

### Key Documentation Files

- `main.c` - Main program flow and command handling
- `organ.c` - Core note generation using timer compare output
- `USART.c` - Serial communication implementation
- `scale16.h` - Musical note frequency lookup table
- `pre_defined_songs.c` - Song data structures and playback

---

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Priorities

- [ ] Non-blocking song playback (timer interrupts)
- [ ] Circular buffer for UART RX (queue system)
- [ ] Volume control (PWM-based)
- [ ] Additional octave support
- [ ] MIDI input compatibility
- [ ] LCD display for current mode
- [ ] Record and playback functionality

---

## 📝 License

This project is open source. You may modify and distribute it freely.

---

## 🙏 Acknowledgments

- **ATmega168** community and avr-libc developers
- **John Williams** for the iconic Imperial March
- Open source tools: avr-gcc, avrdude, make, doxygen

---

## 📞 Contact & Support

- **Issues:** [GitHub Issues](https://github.com/luka7634/AVR-Square-Wave-Organ/issues)
- **Documentation:** See `docs/` folder after running doxygen
- **Author:** Roybel Carbonell Camejo

---

## ⭐ Star History

If you find this project useful, please consider giving it a star ⭐ on GitHub!

---

## 📖 Appendix

### A. Frequency Calculation Formula

```
Frequency = 16,000,000 / (2 × OCR × Prescaler)

Where:
- OCR = Timer Output Compare Register value
- Prescaler = 1, 8, 64, 256, or 1024
```

### B. Adding New Songs

```c
void play_custom_song(void)
{
    const uint16_t notes[] = {C4, D4, E4, F4, G4, A4, B4, C5};
    const uint16_t durations[] = {Q, Q, Q, Q, Q, Q, Q, H};
    
    for (uint8_t i = 0; i < 8; i++)
        playNote(notes[i], durations[i]);
}
```

### C. Baud Rate Error Calculations

| Baud Rate | UBRR Value | Actual Baud | Error |
|-----------|-----------|-------------|-------|
| 2400 | 416 | 2400.0 | 0.0% |
| 4800 | 207 | 4807.7 | 0.16% |
| 9600 | 103 | 9615.4 | 0.16% |
| 19200 | 51 | 19230.8 | 0.16% |
| 38400 | 25 | 38461.5 | 0.16% |
| 115200 | 8 | 111111.1 | -3.5% |

