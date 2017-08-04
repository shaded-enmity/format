def test():
   x = 'aha'
   y = 1.0
   return '{x} is {y}'.format(x=x, y=y)

for _ in range(10000000):
  test()
