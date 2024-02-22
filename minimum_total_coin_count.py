
INIT = 0xffffff
VALUE = 100000000
d = [INIT] * (VALUE + 1)
coins = [2, 3, 5, 7]

d[0] = 0
for i in range(VALUE + 1):
    for j in coins:
        if (i - j) >= 0 and d[i - j] != INIT:
            d[i] = min(d[i], d[i - j] + 1)
#print(d)
print(d[VALUE] if d[VALUE] != INIT else -1)
