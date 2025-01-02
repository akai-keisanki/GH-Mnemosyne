import flask
import src.gen as gen
import json

class Mne:

    def __init__(self, name) -> None:

        self.app = flask.Flask(name)

        return


    def setPages(self) -> None:

        @self.app.route('/')
        def index():
            return start()

        @self.app.route('/start')
        def start():
            """
            Introductory page.
            """

            return 'start page'

        @self.app.route('/return')
        def ret():
            return f'{flask.request.args.get("code", default = 0, type = int)}'

        @self.app.route('/gen/stt')
        def gen_make():
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

            r_hor = gen.gen_hors(len(c), flask.request.json['weekly working day amount'], flask.request.json['schedules per day'], td)[0]
            r_hor = gen.lab_hor(r_hor, c, t, d)

            return str(json.dumps(r_hor))

        return


    def run(self) -> None:

        self.app.run(debug = True)

        return
