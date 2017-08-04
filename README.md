# Locally interpolating format function

This Python2 module implementes simple string interpolation similar to [Python3.6's PEP-498](https://www.python.org/dev/peps/pep-0498/)
with almost negligible performance overhead.

## Example

```python
from format import format as f
def test_func():
  a = 1
  b = 2
  c = 'test'
  return f('{a} != {b} and this was just a {c}')

print(test_func())
```

## License

MIT
