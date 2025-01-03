from src.ui import *

if __name__ == '__main__':

    global app

    mne : Mne = Mne(__name__)

    app = Mne.app

    mne.setRoutes()

    mne.run()
