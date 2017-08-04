#include <Python.h>
#include <frameobject.h>
#include <stdio.h>

#define ERR_BUF_SIZE 512

static void *_raise(PyObject *f, char *spec, PyObject *exc_type) {
  char message[ERR_BUF_SIZE];
  char *name_str = NULL;
  PyObject *type = NULL;
  PyObject *type_name = NULL;

  type = PyObject_Type(f);
  type_name = PyObject_Str(type);
  name_str = PyString_AsString(type_name);

  Py_XDECREF(type);
  Py_XDECREF(type_name);

  snprintf(message, ERR_BUF_SIZE, spec, name_str);
  PyErr_SetString(exc_type, message);

  return NULL;
}

static PyObject *format(PyObject *self, PyObject *f) {
  PyThreadState *state = NULL;
  PyObject *r = NULL;
  PyObject *m = NULL;

  state = PyThreadState_GET();

  if (!(PyUnicode_Check(f) || PyString_Check(f)))
    return _raise(f, "Argument must be `str` or `unicode` not %s",
                  PyExc_TypeError);

  m = PyObject_GetAttrString(f, "format");
  if (!m)
    return _raise(f, "No `format` method found on object: %s",
                  PyExc_AttributeError);

  if (!state->frame->f_locals)
    PyFrame_FastToLocals(state->frame);

  r = PyObject_Call(m, f, state->frame->f_locals);
  Py_XDECREF(m);

  return r;
}

static PyMethodDef format_methods[] = {
    {"format", format, METH_O, "format a string using local variables"},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initformat() {
  Py_InitModule3("format", format_methods,
                 "Faux string interpolation in Python 2.7");
}
