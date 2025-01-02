import flask

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
            return 'start page'

        @self.app.route('/mul')
        def mul():
            a = flask.request.args.get('a', type = int)
            b = flask.request.args.get('b', type = int)
            return f'{a * b}'

        @self.app.route('/gen/make')
        def gen_make():
            horpd = flask.request.json['schedules per day']
            days = flask.request.json['weekly working days']
            profs = flask.request.json['teacher amount']
            ...
            return str(flask.request.json['title'])

        return


    def run(self) -> None:

        self.app.run(debug = True)

        return
