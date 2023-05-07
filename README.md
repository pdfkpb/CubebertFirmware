# CubebertFirmware
Firmware Repo for Cubebert, imported as ExternalProject from Cubebert
Note: Will only bother to test compiling this on an RPI

## Getting Started

### Prerequisites
- Raspberry Pi >= 3
- RPi Pico SDK Installed // See [Pico SDK Getting Started](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- CMake >= 3.10

### Building
```sh
mkdir build
cd build

# If using PIcoW add this parameter  -DPICO_BOARD=pico_w
cmake .. -DPICO_SDK_PATH=$PICO_SDK_PATH
make
```

### Running
Gotta load it on to the Pico, but I'll figure out how to do that later

## License

This project is licensed under the MIT License - see the LICENSE file for details
