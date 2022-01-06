# Processy Framework
Arduino nano task manager firmware designed in object-oriented way.

Project page at [Hackaday.io](https://hackaday.io/project/183221-processy-framework)

## Requirements
* Grunt: The JavaScript Task Runner https://gruntjs.com/
* Arduino CLI (optional) https://arduino.github.io/arduino-cli/

## Important!
Build script tasks:
1. grunt task "grunt-h2cpp-parser" parses source files and copies them to "firmware" folder
2. arduino-cli used to compile firmware.ino and tries to upload binary to COM5

build setting defined in "Gruntfile.js"

## Features
* Message-driven communication
* Low coupling
* Tiny size footprint
* Resource allocation monitor, example:

		21:02:46.508 -> ----- PROC SUMMARY (for 10000ms) -----
		21:02:46.541 -> 101: 0ms (0%)
		21:02:46.541 -> 301: 4ms (0%)
		21:02:46.574 -> 223: 0ms (0%)
		21:02:46.574 -> 302: 10ms (0%)
		21:02:46.608 -> MEM FREE:900
		21:02:46.608 -> --------------------------------------

* Beautiful code :)

## Projects, using this framework ##
* https://github.com/jumangee/EcoSenseAtclock
