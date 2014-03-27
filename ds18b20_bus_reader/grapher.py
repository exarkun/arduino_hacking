from sys import stdin
from datetime import datetime

def main():
    for line in stdin:
        if b"No more addresses." in line:
            continue
        pieces = line.split()
        timestamp = datetime.strptime(pieces.pop(0), b"%Y-%m-%dT%H:%M:%S.%f")
        mapping = dict(piece.split(b"=", 1) for piece in pieces)
        print timestamp.isoformat(), mapping[b"ADDRESS"], mapping[b"TEMP"][:-3]

main()

# set format x "%b %d\n%H:%M"
# set timefmt "%Y-%m-%dT%H:%M:%S"
# set xdata time
# set xlabel "Time"
# set ylabel "Temp (C)"
# plot [ ] [0:25] '/tmp/sensor-a.txt' using 1:3, '/tmp/sensor-b.txt' using 1:3
