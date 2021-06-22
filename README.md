# Sample C++ app for Epsilon

[![Build](https://github.com/numworks/epsilon-sample-app-cpp/actions/workflows/build.yml/badge.svg)](https://github.com/numworks/epsilon-sample-app-cpp/actions/workflows/build.yml)

<img src="/doc/screenshots.gif?raw=true" alt="Sample C++ app for the NumWorks graphing calculator" width="300" align="right">

This is a sample C++ app to use on a [NumWorks calculator](https://www.numworks.com).

```cpp

using namespace EADK;

void eadk_main() {
  Display::pushRectUniform(
    Display::Rect(0, 0, 320, 240),
    Display::Color(0x000000)
  );
  while (1) {
    Keyboard::State kbd = Keyboard::scan();
    if (kbd.keyDown(Keyboard::Key::OK)) {
      spaceship.createRockets();
    }
    if (kbd.keyDown(Keyboard::Key::Up)) {
      spaceship.move(0, -Spaceship::k_step);
    }
    refreshScene();
  }
}
```

## Build the app

You need to install an embedded ARM toolchain and a couple Python modules.

```shell
brew install numworks/tap/arm-none-eabi-gcc # Or equivalent on your OS
pip3 install lz4 pypng
make clean && make build
```

## Run the app

The app is sent over to the calculator using the DFU protocol over USB.

```shell
brew install dfu-util # Or equivalent on your OS
# Now connect your NumWorks calculator to your computer using the USB cable
make run
```

## Notes

The NumWorks calculator runs [Epsilon](http://github.com/numworks/epsilon), a tailor-made calculator operating system. Starting from version 16, Epsilon allows installing custom binary apps. To run this sample app, make sure your calculator is up-to-date by visiting https://my.numworks.com. Note that at the moment Epsilon 16 is in beta, so you'll need to register as [a beta tester](https://my.numworks.com/user/beta).

Epsilon expects apps to follow a certain layout in memory. Namely, they should start with the following header:

|Offset| Size | Value      | Description                  |
|------|------|------------|------------------------------|
| 0x00 | 0x04 | 0xDEC0BEBA | Magic start-of-header marker |
| 0x04 | 0x04 | 0x00000000 | API Level |
| 0x08 | 0x04 | -          | Offset from start of the app to a NULL-terminated NFKD UTF-8 string containing the app name |
| 0x0C | 0x04 | -          | Size of the icon data |
| 0x10 | 0x04 | -          | Offset from start of the app to the actual icon data. This data should be the result of LZ4-compressing a sequence of 55x56 RGB565 pixels |
| 0x14 | 0x04 | -          | Offset from start of the app to the entry point. |
| 0x18 | 0x04 | -          | Size of the entire app |
| 0x22 | 0x04 | 0xDEC0BEBA | Magic end-of-header marker |

Generating the appropriate header is taken care of by a [linker script](/eadk/eadk.ld) when you run `make build`. Once the corresponding binary is built on your computer, you will need to install it at address `0x90350000` and `0x90750000` in your calculator's Flash memory. The included [run.py](/eadk/run.py) script will take care of this for you when you call `make run`.

Due to the embedded nature of Epsilon, the C++ app has to be `no_std`. The interface that an app can use to interact with the OS is essentially a short list of system calls. Feel free to browse the [code of Epsilon](http://github.com/numworks/epsilon) itself if you want to get an in-depth look.

Please note that any custom app is removed when resetting the calculator.

## License

This sample app is distributed under the terms of the BSD License. See LICENSE for details.

## Trademarks

NumWorks is a registered trademark.

