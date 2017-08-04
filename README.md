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

>>> print(test_func())
'1 != 2 and this was just a test'
```

Note that the library enforces the first argument to be a string literal in order to prevent potentional misuse:

```python
>>> from format import format as f
>>> a = 'hmm'
>>> f(a)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
SyntaxError: Argument to format() must be string literal
```

## License

MIT
