from src.ui import *

global app

if __name__ == '__main__':

    app = flask.Flask(__name__)

    mne : Mne = Mne(app)

    app = Mne.app

    mne.setRoutes()

    mne.run()
