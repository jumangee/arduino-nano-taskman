# Processy Framework
Arduino nano task manager firmware designed in object-oriented way

## Requirements
* GruntThe JavaScript Task Runner https://gruntjs.com/
* Arduino CLI (optional) https://arduino.github.io/arduino-cli/

## Important!
Build script tasks:
1. grunt task "grunt-h2cpp-parser" parses source files and copies them to "firmware" folder
2. arduino-cli used to compile firmware.ino and tries to upload binary to COM5

build setting defined in "Gruntfile.js"

## Why?
* Every process (task) has its own scope
* Message-driven communication
* Low coupling

## Your firmware
1. Define firmware process clasess extending IFirmwareProcess
2. Define your firmware class and fill process list factory
