#include <unsigned>
#include <vector>
#include <tuple>
#include <set>
#include <cstdlib>
#include <cmath>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class GenClass
{
private:

  unsigned days, hor_pd, profn, clasn, genn, popn, mutp;
  signed long seed;
  std::vector<std::tuple<unsigned, std::vector<std::vector<unsigned>>, std::vector<std::tuple<unsigned, unsigned>>>> profs;

  std::vector<std::vector<std::tuple<unsigned, unsigned>>> pop;

public:

  GenClass (unsigned days, unsigned hor_pd, unsigned profn, unsigned clasn, std::vector<std::tuple<unsigned, std::vector<std::vector<unsigned>>, std::vector<std::tuple<unsigned, unsigned>>>> profs, signed long seed, unsigned genn, unsigned popn, unsigned mutp)
  : days(days), hor_pd(hor_pd), profn(profn), clasn(clasn), profs(profs.begin(), profs.end()), seed(seed), genn(genn), popn(popn), mutp(mutp)
  {
    srand(seed); srand(rand());
  }


  std::vector<std::tuple<unsigned, unsigned>> makeGen()
  {
    std::vector<std::tuple<unsigned, unsigned>> out(clasn*days*hor_pd);

    std::vector<std::tuple<unsigned, unsigned>> pd;
    unsigned lc = 0;

    for (unsigned c = 0; c < clasn; c ++)
      for (unsigned d = 0; d < days; d ++)
        for (unsigned h = 0; h < hor_pd; h ++)
          while (true) // procurando professor com uma ou mais matérias na classe
          {
            std::get<0>(out[days*hor_pd*c + hor_pd*d + h]) = rand() % profn;
            pd = std::get<1>(profs[std::get<0>(out[days*hor_pd*c + hor_pd*d + h])])[c];
            if (!pd.empty())
            {
              std::get<1>(out[days*hor_pd*c + hor_pd*d + h]) = pd[rand() % pd.size()];
              break;
            }
            if (lc > 3*profn)
            {
              out[days*hor_pd*c + hor_pd*d + h] = std::make_tuple(profn, 0);
              lc = 0; break;
            }
            lc ++;
          }

    return out;
  } 


  signed long gnmFit (const std::vector<std::tuple<unsigned, unsigned>>>>& gen)
  {
    signed long fit = 0;

    /*
      WIP

    TODO: DO
      
    checks

    - [x] conflito de professores
    - [x] descumprimentos de cargas
    - [ ] desequilibrio de cargas
    - [x] horários indisponíveis
    */

    unsigned ps;
    std::set<unsigned> ps;
    std::vector<unsigned> ch(profn, 0);

    for (unsigned d = 0; d < days; d ++)
      for (unsigned h = 0; h < hor_pd; h ++)
      {
        for (unsigned c = 0; c < clasn; c ++)
        {
          pf = std::get<0>(gen[days*hor_pd*c + hor_pd*d + h]);
          if (pf >= profn) // aula vaga
          { fit -= 15; continue; }
          if (ps.find(pf) != ps.end()) // professor onipresente
          { fit -= 20; continue; }
          ps.insert(pf); // adicionar professor à conta
          ch[pf] += 1;
        }
        ps.clear();
      }

    for (unsigned p = 0; p < profn; p ++) // diferença na carga horária
      fit -= abs(std::get<0>(profs[p]) - ch[p]);

    return fit;
  }


  bool deltaFit (const std::vector<std::tuple<unsigned, unsigned>>>>& gen1, const std::vector<std::tuple<unsigned, unsigned>>>>& gen2)
  {
    return gnmFit(gen1) > gnmFit(gen2);
  }


  std::vector<std::tuple<unsigned, unsigned>> genCrs (const std::vector<std::tuple<unsigned, unsigned>>& gen1, const std::vector<std::tuple<unsigned, unsigned>>& gen2)
  {
    std::vector<std::tuple<unsigned, unsigned>> gen3(gen1.size());
    
    unsigned lc = 0;

    for (unsigned long i = 0; i < gen3.size(); i ++)
    {
      if (rand() % 100 < mutp)
        while (true) // adicionando um professor com uma ou mais matérias na classe
        {
          std::get<0>(g3[i]) = rand() % profn;
          pd = std::get<1>(profs[std::get<0>(gen3[i])])[floor(i/hor_pd/days)];
          if (!pd.empty())
          {
            std::get<1>(gen3[i]) = pd[rand() % pd.size()];
            break;
          }
          if (lc > 200)
          {
            gen3[i] = (rand() % 2 == 1) ? gen1[i] : gen2[i];
            lc = 0; break;
          }
          lc ++;
        }
      else
        gen3[i] = (rand() % 2 == 1) ? gen1[i] : gen2[i];
    }
    

    return gen3;
  }


  void genLoop()
  {
    pop.resize(popn);
    
    for (std::vector<std::tuple<unsigned, unsigned>>& gen : pop)
      gen = makeGen();
    
    for (unsigned g = 0; g < genn; g ++)
    {
      for (unsigned i = 0; i < popn; i ++)
	pop.push_back(genCrs(pop[rand() % popn], pop[rand() % popn]));
      
      std::sort(pop.begin(), pop.end(), deltaFit);
      pop.resize(popn);
    }
  }

  
  std::vector<std::vector<std::tuple<unsigned, unsigned>>> getPop()
  {
    return pop;
  }
};


std::vector<std::vector<std::tuple<unsigned, unsigned>>> genhor (unsigned days, unsigned hor_pd, unsigned profn, unsigned clasn, std::vector<std::tuple<unsigned, std::vector<std::vector<unsigned>>, std::vector<std::tuple<unsigned, unsigned>>>> profs, signed long seed, unsigned genn = 128, unsigned popn = 100, unsigned mutp = 5)
{
  /* Função para execução da script de geração de horários.
   *
   * Observações
   * -----------
   * Fornecer uma mesma seed pode levar a resultados idênticos
   * por causa do uso da função rand() do header <cstdlib>,
   * incluso no G++, GCC.
   */

  GenClass gc(days, hor_pd, profn, profs, seed, genn, popn, mutp);

  gc.genLoop();

  return gc.getPop();
}


PYBIND11_MODULE(genhor, m)
{
  m.def("genhor", &genhor, "Função para execução da script de geração de horários.");
}

