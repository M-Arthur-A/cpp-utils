#include <pybind11/pybind11.h>

namespace py = pybind11;

float some_fn(float arg1, float arg2) {
    return arg1 + arg2;
}

class SomeClass {
public:
SomeClass(float m_): multiplier(m_) {};

float multiply(float input) {
    return multiplier * input;
}

private:
float multiplier;
};

PYBIND11_MODULE(module_name, handle) {
    handle.doc() = "This is the module docs. 1st try";
    handle.def("some_fn_python_name", &some_fn);
    
    py::class_<SomeClass>(handle, "PySomeClass")
        .def(py::init<float>())
        .def("multiply", &SomeClass::multiply)
        ;
}