from format import format as f
def test():
   x = 'aha'
   y = 1.0
   return f('{x} is {y}')

for _ in range(10000000):
  test()
