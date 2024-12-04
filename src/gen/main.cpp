#include <string>
#include <vector>
#include <tuple>
#include <map>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


std::map<std::string, std::vector<std::vector<std::tuple<std::string, std::string>>>> genhor (unsigned days, unsigned hor_pd, std::map<std::string, std::tuple<unsigned, std::vector<std::string>, std::vector<std::pair<unsigned, unsigned>>>> profs)
{
  /* Função para execução da script de geração de horários. */

  // WIP

  return std::map<std::string, std::vector<std::vector<std::tuple<std::string, std::string>>>>();
}


PYBIND11_MODULE(genhor, m)
{
  m.def("genhor", &genhor, "Função para execução da script de geração de horários.");
}
