#include <pybind11/pybind11.h>

signed genhor(signed& x)
{
  x *= 3;

  return 0;
}

PYBIND11_MODULE(genhor, m)
{
  m.def("f", &f, "Função.");
}
