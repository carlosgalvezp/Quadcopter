#!/usr/bin/python3
import argparse
import sys
import os
import shutil

from tools.pyjobs.build_docker import DockerBuilder
from tools.pyjobs.build_fc import FlightControllerBuilder

def main(cmd):
    if cmd == 'build-docker':
        DockerBuilder().run()

    elif cmd == 'build-fc':
        FlightControllerBuilder().run()

    elif cmd == 'clean':
        if os.path.exists('build'):
            shutil.rmtree('build')
    else:
        print('Unknown command {}'.format(cmd))
        return -1

    return 0

if __name__ == '__main__':
    main(sys.argv[1])
