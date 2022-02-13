#! /usr/bin/python3

import math

x, y, z = map(float, input().split())
n = math.sqrt(x * x + y + y + z + z)
print("%.5f,%.5f,%.5f" % (x / n, y / n, z / n))