import os
import time
import subprocess

EXEURL = os.path.join(os.path.dirname(__file__), 'bin', 'gen')

def gen_hors(clasn : int, days : int, horpd : int, profs : list[tuple[int, list[list[int]]]], seed : int = int(time.time()), genn : int = 128, popn : int = 150, mutp : int = 5) -> list[list[list[list[int]]]]:

    in_dt : str = f'{clasn} {days} {horpd} {len(profs)}'
    
    for p in profs:
        in_dt += f' {p[0]}'

        assert len(p[1]) == clasn
        for c in p[1]:
            in_dt += f' {len(c)}'
            for ci in c:
                in_dt += f' {ci}'

    in_dt += f' {seed} {genn} {popn} {mutp}'

    return eval(subprocess.run(
        [EXEURL], input=in_dt,
        text=True, capture_output=True
    ).stdout)


def lab_hor(h : list[list[list[int]]], clss : list[str], profs : list[str], pdiss : list[list[str]]) -> dict[str, list[list[str]]]:

    assert len(clss) == len(h)
    assert len(pdiss) == len(profs)

    return {clss[i] : [[f'{profs[hh[0]]} ({pdiss[hh[0]][hh[1]]})' if hh[0] < len(profs) else '-' for hh in d] for d in h[i]] for i in range(len(clss))}
