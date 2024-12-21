#include <unsigned>
#include <vector>
#include <tuple>
#include <cstdlib>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


std::vector<std::vector<std::vector<std::tuple<std::unsigned, std::unsigned>>>> makeGen(unsigned days, unsigned hor_pd, unsigned profn, unsigned discn, unsigned clasn, std::vector<std::tuple<unsigned, std::vector<std::tuple<std::unsigned, std::unsigned>>, std::vector<std::tuple<unsigned, unsigned>>>> profs)
{
  std::vector<std::vector<std::vector<std::tuple<std::unsigned, std::unsigned>>>> out;
  out.resize(clasn);

  for (unsigned c = 0; c < clasn)
  {
    out[c].resize(days);
    for (unsigned d = 0; d < days; d ++)
    {
      out[c][d].resize(hor_pd);
      for (unsigned h = 0; h < hor_pd; h ++)
      {
        std::get<0>(out[c][d][h]) = rand() % profn();
        std::get<1>(out[c][d][h]) = rand() % discn();
      }
    }
  }

  return out;
}


signed long gen_fit (std::vector<std::vector<std::vector<std::tuple<std::unsigned, std::unsigned>>>> gen)
{
  signed long fit = 0;

  // ...

  return fit;
}


std::map<std::unsigned, std::vector<std::vector<std::tuple<std::unsigned, std::unsigned>>>> genhor (unsigned days, unsigned hor_pd, unsigned profn, unsigned discn, unsigned clasn, std::vector<std::tuple<unsigned, std::vector<std::tuple<unsigned, unsigned>>, std::vector<std::tuple<unsigned, unsigned>>>> profs, unsigned n, signed long seed)
{
  /* Função para execução da script de geração de horários. */

  std::vector<std::vector<std::vector<std::tuple<std::unsigned, std::unsigned>>>> out;

  /*
  Rápida descrição das variáveis iniciais:

  days : unsigned - Número de dias por tabela

  hor_pd : unsigned - Número de horas por dia

  profn : unsigned - número de professores

  discn : unsigned - número de disciplinas

  clasn : unsigned - número de turmas

  profs : map - mapa de professores onde:
    profs[professor : unsigned] = (carga_horaria : unsigned, t_e_d : vector, indisp : vector) - onde:
      t_e_d[i] = (turma : unsigned, disciplina : unsigned)
      indisp[i] = (dia_indisp : unsigned, hora_indisp : unsigned)

  n : unsigned - número de gerações

  seed : signed long - seed das gerações

  out : map - mapa de turmas x horarios onde:
    out[turma : unsigned] = horario : vector - um horario, vetor de dias onde:
      horario[i] = dia : vector - um dia, vetor de horarios onde:
        dia[i] = (professor : unsigned, disciplina : unsigned)
  */

  /*
  Ideia do algoritmo:

  - [ ] Criar genomas
    - [ ] Sempre criar genomas aleatórios válidos
  - [ ] Criar critérios de fitness
    - [ ] Punições para invalidades
    - [ ] Punições e promoções de equilíbrio
    - [ ] Promoções com base em pesquisa
    - [ ] ajustar parâmetros e taxas
  - [ ] Criar geração principal e testes
    - [ ] .
  */

  return out;
}


PYBIND11_MODULE(genhor, m)
{
  m.def("genhor", &genhor, "Função para execução da script de geração de horários.");
}
