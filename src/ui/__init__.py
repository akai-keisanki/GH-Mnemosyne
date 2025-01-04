import flask
import src.gen as gen
import requests
import json
from time import time
import random

class Mne:

    def __init__(self, name) -> None:
        
        self.app = flask.Flask(name, template_folder='templates')
        random.seed(int(time()))

        return


    def setRoutes(self) -> None:

        # User Interface

        @self.app.route('/')
        def index():
            return start()

        @self.app.route('/start')
        def start():
            """
            Introductory page.
            """

            return flask.render_template('start.html')

        @self.app.route('/gen/form')
        def gen_form():
            """
            Generation formulary.
            """

            return flask.render_template('gen/form.html', rand = random.randint(-100000000, 100000000))

        @self.app.route('/gen/up')
        def gen_up():
            dt : dict = dict(flask.request.args)
            dt['teachers'] = dict()

            seed = dt['seed']
            dt.pop('seed')

            for k in dt.copy():
                if 'p:' in k:
                    tmp = k.split(':')
                    if tmp[1] not in dt['teachers'].keys():
                        dt['teachers'][tmp[1]] = dict()
                    dt['teachers'][tmp[1]][tmp[2]] = dt[k]
                    dt.pop(k)

            dt['classrooms'] = [s.strip() for s in dt['classrooms'].split(',')]

            for t in dt['teachers']:
                dt['teachers'][t]['schedules per week'] = int(dt['teachers'][t]['schedules per week'])
                dt['teachers'][t]['subjects'] = dict()
                for c in dt['classrooms']:
                    dt['teachers'][t]['subjects'][c] = list()
                for s in [[sj.split('-')[0].strip(), sj.split('-')[1].strip()] for sj in dt['teachers'][t]['subj'].split(',')]:
                    dt['teachers'][t]['subjects'][s[0]].append(s[1])
                dt['teachers'][t].pop('subj')

            dt['weekly working day amount'] = int(dt['weekly working day amount'])
            dt['schedules per day'] = int(dt['schedules per day'])
            dt = requests.get(flask.url_for('gen_stt', _external=True), json = dt, params = {'seed': seed}).json()
            return flask.render_template('gen/result.html', dt = dt)

        # Application Programming Interface

        @self.app.route('/return')
        def ret():
            return f'{flask.request.args.get("code", default = 0, type = int)}'

        @self.app.route('/gen/stt')
        def gen_stt():
            """
            Generate a school timetable through API.

            Notes
            -----
            JSON format:
            ```
            {
                "classrooms": [str],
                "weekly working day amount": int,
                "schedules per day": int,
                "teachers":
                {
                    "<teacher>":
                    {
                        "schedules per week": int,
                        "subjects":
                        {
                            "<classroom>": [str],
                            ...
                        }
                    },
                    ...
                }
            }
            ```
            """

            c = flask.request.json['classrooms']
            t = []
            d = []
            td = []

            turdis = []

            for ti, tc in flask.request.json['teachers'].items():
                t.append(ti)
                d.append([])

                turdis = [[] for _ in range(len(c))]

                for s, dis in tc['subjects'].items():
                    for di in dis:
                        if di not in d[len(t)-1]: d[len(t)-1].append(di)
                    turdis[c.index(s)] = [d[len(t)-1].index(di) for di in dis]

                td.append((tc['schedules per week'], turdis))

            r_hor = gen.gen_hors(len(c), flask.request.json['weekly working day amount'], flask.request.json['schedules per day'], td, flask.request.args.get('seed', default = int(time()), type = int), flask.request.args.get("gens", default = 128, type = int))[0]
            r_hor = gen.lab_hor(r_hor, c, t, d)

            return str(json.dumps(r_hor))

        return


    def run(self) -> None:

        self.app.run(debug = False)

        return
