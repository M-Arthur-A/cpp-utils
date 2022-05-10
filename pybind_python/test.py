import os
os.chdir('/home/arthur/Project/mySoft/Cpp/pybind_python/')

from build.module_name import *

print(some_fn_python_name(5,77))
cl = PySomeClass(123)
print(cl.multiply(11))
