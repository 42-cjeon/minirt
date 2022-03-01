#! /usr/bin/python3

import math

W = False
E = True

S = False
N = True

ER = 6371
R = 1700 + ER
THETA = 37
PI = 127

if E:
	PI += 90
elif W:
	PI = -PI + 90
if S:
	THETA += 90
elif N:
	THETA = 90 - THETA

THETA = THETA / 180 * math.pi
PI = PI / 180 * math.pi
x = R * math.sin(THETA) * math.cos(PI)
y = R * math.cos(THETA)
z = R * math.sin(THETA) * math.sin(PI)

n = math.sqrt(x * x + y * y + z * z)
od = "%.5f,%.5f,%.5f %.5f,%.5f,%.5f" % (x, y, z, -x / n, -y / n, -z / n)
print(f"C {od} 60 1")
print(f"li {od} 180 0.8 255,255,255")