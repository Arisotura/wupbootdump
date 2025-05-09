import sys, serial


if len(sys.argv) < 3:
    print("usage: dump.py <serialport> <output>")
    sys.exit(-1)


try:
    fin = open('wupbootdump.bin', 'rb')
except FileNotFoundError:
    print("could not open payload file")
    sys.exit(-1)

fout = open(sys.argv[2], 'wb')

try:
    ser = serial.Serial(sys.argv[1], 115200, timeout=1)
except serial.serialutil.SerialException:
    print("could not open serial port")
    fin.close()
    sys.exit(-1)

fin.seek(0, 2)
flen = fin.tell()
fin.seek(0, 0)

print("binary length: {} bytes".format(flen))

# send payload length
plen = 0x3FFF28
print("sending payload length...")
ser.write(plen.to_bytes(4, byteorder='little'))

# send dummy bytes up to 0x3F0000
dummy = bytearray(0x10000)
for i in range(0,0x3F):
    print("sending dummy... {}/62".format(i))
    ser.write(dummy)

# send binary
print("sending binary...")
ser.write(fin.read(flen))
fin.close()

# send trail
print("sending trail...")
tlen = 0xFF24 - flen
tdummy = bytearray(tlen)
ser.write(tdummy)

entry = 0x3F0000
ser.write(entry.to_bytes(4, byteorder='little'))

print("waiting for incoming data...")

fout.write(ser.read(0x1000))
fout.close()

print("done!")
