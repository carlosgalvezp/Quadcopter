#!/usr/bin/python3
import argparse
import sys
import os
import shutil

from tools.pyjobs.build_docker import DockerBuilder
from tools.pyjobs.build_fc import FlightControllerBuilder
from tools.pyjobs.upload_fc import FlightControllerUploader
from tools.pyjobs.gui import GUIBuilder
from tools.pyjobs.gui import GUIRunner

def main(cmd):
    if cmd == 'build-docker':
        DockerBuilder().run()

    elif cmd == 'build-fc':
        FlightControllerBuilder().run()

    elif cmd == 'clean':
        if os.path.exists('build'):
            shutil.rmtree('build')

    elif cmd == 'upload':
        FlightControllerBuilder().run()
        FlightControllerUploader().run()

    elif cmd == 'build-gui':
        GUIBuilder().run()

    elif cmd == 'gui':
        GUIBuilder().run()
        GUIRunner().run()

    else:
        print('Unknown command {}'.format(cmd))
        return -1

    return 0

if __name__ == '__main__':
    main(sys.argv[1])
