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

You need to install an embedded ARM toolchain and [nwlink](https://www.npmjs.com/package/nwlink).

```shell
brew install numworks/tap/arm-none-eabi-gcc node # Or equivalent on your OS
npm install -g nwlink
make
```

Once you `target/voord.nwa` app is built, you can upload it onto your calculator from [NumWorks online uploader](https://my.numworks.com/apps).

## Run the app (development)

The app is sent over to the calculator using the DFU protocol over USB.
The last command has to be executed with the targeted device plugged into the computer.

```shell
# Now connect your NumWorks calculator to your computer using the USB cable
make run
```

## Requirements of nwa files

A `.nwa` file is an ELF file that has the following symbols defined:
- `eadk_app_name`: this is the address of the string representing the name of the app. It will be displayed in the Home of Epsilon. This symbol should be in the `.rodata.eadk_app_name` section.
- `eadk_app_api_level`: this is a 4-byte integer stating which version of eadk/eadk.s the external app relies on.  It is expected to be in the `.rodata.eadk_app_api_level` section.
- `eadk_app_icon`: this symbol should be defined in the `.rodata.eadk_app_icon` section and contain the raw NWI data for the icon. Using `nwlink` you can convert a 55x56 png icon into a NWI format. The NWI format is a raw little-endian RGB565 bitmap that is then LZ4-compressed.
- `_eadk_main`, the entry point of the application.

Optionally, if the external app needs custom binary data, it can reference the `eadk_external_data` symbol. If so, the [NumWorks online uploader](https://my.numworks.com/apps) will ask for the external data to be provided after dropping the `.nwa` file. In development, you can provide the `--external-data` flag to `nwlink install-nwa`.

## Notes

The NumWorks calculator runs [Epsilon](http://github.com/numworks/epsilon), a tailor-made calculator operating system. Starting from version 16, Epsilon allows installing custom binary apps. To run this sample app, make sure your calculator is up-to-date by visiting <https://my.numworks.com>.

Due to the embedded nature of Epsilon, this C++ app is built using `-ffreestanding -nostdinc -nostdlib`. The interface that an app can use to interact with the OS is essentially a short list of system calls. Feel free to browse the [code of Epsilon](http://github.com/numworks/epsilon) itself if you want to get an in-depth look.

Please note that any custom app is removed when resetting the calculator.

## License

This sample app is distributed under the terms of the BSD License. See LICENSE for details.

## Trademarks

NumWorks is a registered trademark.
