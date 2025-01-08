from src.ui import *


mne : Mne = Mne(__name__)

mne.setRoutes()


app = mne.app


if __name__ == '__main__':

    mne.run(True)
