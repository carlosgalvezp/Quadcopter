Quadcopter [![Build Status](https://travis-ci.org/carlosgalvezp/Quadcopter.svg?branch=master)](https://travis-ci.org/carlosgalvezp/Quadcopter)
==========
Source code Quadcopter Flight Controller, based on Crius AIOP v2.0 (Atmega 2560)

Minimal requirements
--------------------
- Ubuntu 14.04 or later

Setup environment
-----------------

Run `tools/scripts/setup/setup_ubuntu.sh`

Build flight controller firmware
-------------------------------

Run the following command from the root directory:

    $ ./run.py build-fc


Upload flight controller firmware
---------------------------------

    $ ./run.py upload
