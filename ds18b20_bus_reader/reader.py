from twisted.internet.serialport import SerialPort
from twisted.internet import reactor
from twisted.protocols.basic import LineReceiver

from sys import stdout
from datetime import datetime

class Timestamper(LineReceiver):
    delimiter = b"\n"

    def __init__(self, output):
        self.output = output


    def lineReceived(self, line):
        self.output.write("%s %s\n" % (datetime.now().isoformat(), line))


def main():
    SerialPort(Timestamper(stdout), b"/dev/ttyUSB0", reactor)
    reactor.run()

main()

