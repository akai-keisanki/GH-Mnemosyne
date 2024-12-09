#include <string>
#include <vector>
#include <tuple>
#include <map>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


std::map<std::string, std::vector<std::vector<std::tuple<std::string, std::string>>>> genhor (unsigned days, unsigned hor_pd, std::map<std::string, std::tuple<unsigned, std::vector<std::tuple<std::string, std::string>>, std::vector<std::tuple<unsigned, unsigned>>>> profs)
{
  /* Função para execução da script de geração de horários. */

  std::map<std::string, unsigned> disc;
  std::map<std::string, unsigned> prof;

  std::map<std::string, std::vector<std::vector<std::tuple<std::string, std::string>>>> out;

  /*
  Rápida descrição das variáveis iniciais:

  days : unsigned - Número de dias por tabela

  hor_pd : unsigned - Número de horas por dia

  profs : map - mapa de professores onde:
    profs[professor : string] = (carga_horaria : unsigned, t_e_d : vector, indisp : vector) - onde:
      t_e_d[i] = (turma : string, disciplina : string)
      indisp[i] = (dia_indisp : unsigned, hora_indisp : unsigned)

  disc : map - mapa de disciplinas onde:
    disc[disciplina : string] = frequencia de alocacao : unsigned

  prof : map - mapa de professores onde:
    prof[professor : string] = frequencia de alocacao : unsigned

  out : map - mapa de turmas x horarios onde:
    out[turma : string] = horario : vector - um horario, vetor de dias onde:
      horario[i] = dia : vector - um dia, vetor de horarios onde:
        dia[i] = (professor : string, disciplina : string)
  */

  /*
  Ideia do algoritmo:

  - [ ] Percorrer os horários de aula
    - [ ] Criar uma função para determinar a melhor escola para um horário de aula específico
    - [ ] Alocar horários determinados e alterar dados existentes.
  - [ ] Fazer um controle de qualidade de horário, refazendo se preciso.
  */

  return out;
}


PYBIND11_MODULE(genhor, m)
{
  m.def("genhor", &genhor, "Função para execução da script de geração de horários.");
}
