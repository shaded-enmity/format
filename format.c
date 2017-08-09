#include <Python.h>
#include <frameobject.h>
#include <stdio.h>


#define ERR_BUF_SIZE 512
#define LOAD_CONST   100
#define OPCODE_SIZE  3

#if PY_MAJOR_VERSION >= 3
  #define TYPECHECK(f)     PyBytes_Check(f)
  #define UNWRAP_CODE(b)   PyBytes_AS_STRING(b)
  #define UNWRAP_STRING(b) PyUnicode_AsUTF8(b)
#else
  #define TYPECHECK(f)     !(PyUnicode_Check(f) || PyString_Check(f))
  #define UNWRAP_CODE(b)   PyString_AsString(b)
  #define UNWRAP_STRING(b) PyString_AsString(b)
#endif


static void *_raise_typed_error(PyObject *f, char *spec, PyObject *exc_type) {
  char message[ERR_BUF_SIZE];
  char *name_str = NULL;
  PyObject *type = NULL;
  PyObject *type_name = NULL;

  type = PyObject_Type(f);
  type_name = PyObject_Str(type);
  name_str = UNWRAP_STRING(type_name);

  Py_XDECREF(type);
  Py_XDECREF(type_name);

  snprintf(message, ERR_BUF_SIZE, spec, name_str);
  PyErr_SetString(exc_type, message);

  return NULL;
}

static int _check_format_string_is_literal(PyFrameObject *frame) {
  /* check that the function argument is loaded using LOAD_COSNT
   * which means it is a literal value*/
  return frame->f_code->co_code && 
         UNWRAP_CODE(frame->f_code->co_code)[frame->f_lasti - OPCODE_SIZE] == LOAD_CONST;
}

static PyObject *format(PyObject *self, PyObject *f) {
  PyThreadState *state = NULL;
  PyObject *r = NULL;
  PyObject *m = NULL;

  state = PyThreadState_GET();

  if (TYPECHECK(f))
    return _raise_typed_error(f, "Argument must be `str` or `unicode` not %s",
                              PyExc_TypeError);

  if (!_check_format_string_is_literal(state->frame)) {
    PyErr_SetString(PyExc_SyntaxError,
                    "Argument to format() must be string literal");
    return NULL;
  }

  m = PyObject_GetAttrString(f, "format");
  if (!m)
    return _raise_typed_error(f, "No `format` method found on object: %s",
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

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef formatmodule = {
   PyModuleDef_HEAD_INIT, "format", "Faux string interpolation in Python<3.6",
   -1, format_methods};

PyMODINIT_FUNC PyInit_format(void) { return PyModule_Create(&formatmodule); }

#else

PyMODINIT_FUNC initformat() {
  Py_InitModule3("format", format_methods,
                 "Faux string interpolation in Python<3.6");
}

#endif
