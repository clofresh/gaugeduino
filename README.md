# Gaugeduino

An Arduino-powered analog gauge. Provides both the Arduino sketch and a Python
client for submitting data to it via USB.

## Running the client

First you'll need pySerial, if you don't have it already

    easy_install pyserial

Then you can run the client:

    python client/gaugeduino.py
