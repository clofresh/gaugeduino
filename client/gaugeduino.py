import serial
import time
import random
from contextlib import contextmanager

class Gaugediuno(object):
	def __init__(self, device=None, baudrate=None):
		self.device = device or "/dev/tty.usbmodem1d11"
		self.baudrate = baudrate or 28800

	@contextmanager
	def connect(self):
		conn = Serial.init(self.device, self.baudrate)
		try:
			yield conn
		finally:
			conn.close()

class Serial(object):
	delay = 0.2

	@classmethod
	def init(cls, device, baudrate):
		return cls(serial.Serial(device, baudrate))

	def __init__(self, ser):
		self.ser = ser

	def write(self, value):
		formatted = self._format(value)
		self.ser.write(formatted)
		time.sleep(self.delay)

	def close(self):
		self.ser.close()

	def _format(self, value):
		return "{0:02}".format(value)

def main():
	baudrate = 28800
	device = "/dev/tty.usbmodem1d11"
	gauge = Gaugediuno(device, baudrate)
	with gauge.connect() as conn:
		while True:
			val = random.randint(0, 99)
			print val
			conn.write(val)

if __name__ == '__main__':
	main()
