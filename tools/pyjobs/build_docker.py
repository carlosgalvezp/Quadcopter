import os.path
import subprocess

class DockerBuilder(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._registry = 'carlosgalvezp'
        self._tag = '{}/{}'.format(self._registry, 'quadcopter')

    def run(self):
        dockerfile_path = os.path.abspath(os.path.join(self._this_path, '..',
                                                       'docker'))

        cmd = ['docker', 'build', '-t', self._tag, dockerfile_path]
        print('Building docker image...\n{}'.format(' '.join(cmd)))
        subprocess.run(cmd, check=True)
