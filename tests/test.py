import format
def test():
   x = 'aha'
   y = 1.0
   return format.format('{x} is {y}')

for _ in range(10000000):
  test()
