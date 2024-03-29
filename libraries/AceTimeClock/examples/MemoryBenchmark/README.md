# Memory Benchmark

The `MemoryBenchmark.ino` was compiled with each `FEATURE_*` and the flash
memory and static RAM sizes were recorded. The `FEATURE_BASELINE` selection is
the baseline, and its memory usage  numbers are subtracted from the subsequent
`FEATURE_*` memory usage.

**Version**: AceTimeClock v1.2.3

**DO NOT EDIT**: This file was auto-generated using `make README.md`.

## How to Regenerate

To regenerate this README.md:

```
$ make clean_benchmarks
$ make benchmarks
$ make README.md
```

The `make benchmarks` target uses `collect.sh` script which calls `auniter.sh`
(https://github.com/bxparks/AUniter) to invoke the Arduino IDE programmatically.
It produces a `*.txt` file with the flash and ram usage information (e.g.
`nano.txt`). It now takes about 16 minutes to generate the `*.txt` files on my
quad-core Intel Core i7-3840QM CPU @ 2.80GHz laptop.

The `make README.md` command calls the `generated_readme.py` Python script which
generates this `README.md` file. The ASCII tables below are generated by the
`generate_table.awk` script, which takes each `*.txt` file and converts it to an
ASCII table.

## Library Size Changes

**v1.0.0**

* Initial split from AceTime v1.7.5 for v1.8.0.
* Convert `DS3231.h` into a template class for `<AceWire.h>`, replacing direct
  dependency on `<Wire.h>`.
    * Just including the `<Wire.h>` header causes flash memory to be consumed,
      even if `Wire` object is never used.
    * Saves 1000-1500 bytes of flash on AVR processors.
    * Saves 500 bytes of flash on SAMD.
    * Saves 4000 bytes of flash STM32.
    * Saves 500 bytes of flash on ESP8266.
    * Saves 3000-4000 bytes of flash on ESP32.
    * Saves 2500 bytes of flash on Teensy 3.2.
* Add benchmark for `DS3231Clock` separately from `SytemClock`.
* Add benchmarks for `SystemClockCoroutine` separately from `SystemClockLoop`.
* Rename `SystemClock` label to `SystemClockLoop`.

**v1.0.2**

* Fix bad merge in README.md.
* Create benchmarks for 3 variations of `DS3231Clock`: TwoWire, SimpleWire, and
  SimpleWireFast.
    * Make sure `<Wire.h>` is *not* included when using SimpleWireInterface and
      SimpleWireFastInterface.
    * Flash consumption reduced by 1600 bytes using SimpleWireInterface and
      2200 bytes using `SimpleWireInterface` on AVR.
    * Saves 800-8800 bytes of flash on 32-bit processors.

**v1.1.0**

* Upgrade tool chains
    * Arduino IDE from 1.8.16 to 1.8.19
    * Arduino CLI from 0.19.2 to 0.20.2
    * STM32duino from 2.0.0 to 2.2.0
    * AVR Core from 1.8.3 to 1.8.4
    * ESP32 Core from 1.0.6 to 2.0.2
    * Teensyduino from 1.55 to 1.56
* Add benchmark entries for:
    * `StmRtcClock`
    * `Stm32F1Clock`
    * `NtpClock`
    * `EspSntpClock`
* ESP32
    * `NtpClock` and `EspSntpClock` increases flash usage by ~400kB and
      static RAM usage by ~20KB.
    * Such a large increase is *not* seen on the ESP8266.
    * Probably due to `<WiFi.h>`.
* STM32
    * Using `<STM32RTC.h>` through `StmRtcClock` consumes an extra ~4kB of flash
      compared to using `Stm32F1Clock`.

**v1.2.2**

* Upgrade tool chains
    * Arduino CLI from 0.27.1
    * STM32duino from 2.3.0
    * AVR Core from 1.8.4 to 1.8.5
    * ESP32 Core from 2.0.2 to 2.0.5
    * Teensyduino from 1.56 to 1.57
* Upgrade to AceTime v2.0
    * Update `NtpClock` to use AceTime `Epoch::currentEpochYear()`
* Many `Clock` classes increase in flash size
    * AVR: 100-400 bytes
    * ESP8266: 50-150 bytes
    * Most likely due to the adjustable AceTime epoch
      (`Epoch::currentEpochYear()`), and the change from `int8_t` year to
      `int16_t` year.

## Arduino Nano

* 16MHz ATmega328P
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* Arduino AVR Boards 1.8.5

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               |    496/   17 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   |   4958/  259 |   4462/  242 |
| DS3231Clock<SimpleWire>                |   3412/   49 |   2916/   32 |
| DS3231Clock<SimpleWireFast>            |   2742/   43 |   2246/   26 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        |   1016/   72 |    520/   55 |
| SystemClockLoop+1 Basic zone           |   7102/  262 |   6606/  245 |
| SystemClockLoop+1 Extended zone        |  10702/  296 |  10206/  279 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   |   1820/  100 |   1324/   83 |
| SystemClockCoroutine+1 Basic zone      |   7876/  290 |   7380/  273 |
| SystemClockCoroutine+1 Extended zone   |  11476/  324 |  10980/  307 |
+----------------------------------------------------------------------+

```

## Sparkfun Pro Micro

* 16 MHz ATmega32U4
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* SparkFun AVR Boards 1.1.13

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               |   3490/  157 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   |   7948/  405 |   4458/  248 |
| DS3231Clock<SimpleWire>                |   6488/  195 |   2998/   38 |
| DS3231Clock<SimpleWireFast>            |   5704/  189 |   2214/   32 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        |   3972/  212 |    482/   55 |
| SystemClockLoop+1 Basic zone           |  10056/  400 |   6566/  243 |
| SystemClockLoop+1 Extended zone        |  13656/  434 |  10166/  277 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   |   4776/  240 |   1286/   83 |
| SystemClockCoroutine+1 Basic zone      |  10830/  428 |   7340/  271 |
| SystemClockCoroutine+1 Extended zone   |  14430/  462 |  10940/  305 |
+----------------------------------------------------------------------+

```

## STM32 Blue Pill

* STM32F103C8, 72 MHz ARM Cortex-M3
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* STM32duino 2.3.0

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               |  21348/ 3560 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   |  31940/ 3836 |  10592/  276 |
| DS3231Clock<SimpleWire>                |  25348/ 3632 |   4000/   72 |
|----------------------------------------+--------------+--------------|
| StmRtcClock                            |  25840/ 3640 |   4492/   80 |
| Stm32F1Clock                           |  21936/ 3596 |    588/   36 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        |  21792/ 3644 |    444/   84 |
| SystemClockLoop+1 Basic zone           |  26216/ 3648 |   4868/   88 |
| SystemClockLoop+1 Extended zone        |  28256/ 3648 |   6908/   88 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   |  22268/ 3676 |    920/  116 |
| SystemClockCoroutine+1 Basic zone      |  26688/ 3680 |   5340/  120 |
| SystemClockCoroutine+1 Extended zone   |  28732/ 3680 |   7384/  120 |
+----------------------------------------------------------------------+

```

## ESP8266

* NodeMCU 1.0, 80MHz ESP8266
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* ESP8266 Boards 3.0.2

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               | 260109/27896 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   | 269573/28560 |   9464/  664 |
| DS3231Clock<SimpleWire>                | 267365/28176 |   7256/  280 |
|----------------------------------------+--------------+--------------|
| NtpClock                               | 269137/28216 |   9028/  320 |
| EspSntpClock                           | 266637/28240 |   6528/  344 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        | 264809/28124 |   4700/  228 |
| SystemClockLoop+1 Basic zone           | 271365/28688 |  11256/  792 |
| SystemClockLoop+1 Extended zone        | 273957/28832 |  13848/  936 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   | 265353/28156 |   5244/  260 |
| SystemClockCoroutine+1 Basic zone      | 271925/28720 |  11816/  824 |
| SystemClockCoroutine+1 Extended zone   | 274517/28864 |  14408/  968 |
+----------------------------------------------------------------------+

```

## ESP32

* ESP32-01 Dev Board, 240 MHz Tensilica LX6
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* ESP32 Boards 2.0.5

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               | 211077/16056 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   | 254241/16712 |  43164/  656 |
| DS3231Clock<SimpleWire>                | 236477/16384 |  25400/  328 |
|----------------------------------------+--------------+--------------|
| NtpClock                               | 662693/37816 | 451616/21760 |
| EspSntpClock                           | 675649/37684 | 464572/21628 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        | 226601/16368 |  15524/  312 |
| SystemClockLoop+1 Basic zone           | 232041/16384 |  20964/  328 |
| SystemClockLoop+1 Extended zone        | 234405/16384 |  23328/  328 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   | 227213/16400 |  16136/  344 |
| SystemClockCoroutine+1 Basic zone      | 232649/16416 |  21572/  360 |
| SystemClockCoroutine+1 Extended zone   | 235017/16416 |  23940/  360 |
+----------------------------------------------------------------------+

```

RAM usage remains constant as more objects are created, which indicates that an
initial pool of a certain minimum size is created regardless of the actual RAM
usage by objects.

## Teensy 3.2

* 96 MHz ARM Cortex-M4
* Arduino IDE 1.8.19, Arduino CLI 0.27.1
* Teensyduino 1.57

```
+----------------------------------------------------------------------+
| Functionality                          |  flash/  ram |        delta |
|----------------------------------------+--------------+--------------|
| Baseline                               |  10076/ 4160 |      0/    0 |
|----------------------------------------+--------------+--------------|
| DS3231Clock<TwoWire>                   |  17596/ 4992 |   7520/  832 |
| DS3231Clock<SimpleWire>                |  22508/ 4180 |  12432/   20 |
|----------------------------------------+--------------+--------------|
| SystemClockLoop                        |  10852/ 4212 |    776/   52 |
| SystemClockLoop+1 Basic zone           |  23860/ 4212 |  13784/   52 |
| SystemClockLoop+1 Extended zone        |  27104/ 4212 |  17028/   52 |
|----------------------------------------+--------------+--------------|
| SystemClockCoroutine                   |  11616/ 4244 |   1540/   84 |
| SystemClockCoroutine+1 Basic zone      |  24648/ 4244 |  14572/   84 |
| SystemClockCoroutine+1 Extended zone   |  27892/ 4244 |  17816/   84 |
+----------------------------------------------------------------------+

```

