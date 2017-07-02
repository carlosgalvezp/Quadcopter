import os
import subprocess

class FlightControllerUploader(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'build', 'fc')
        self._image = 'carlosgalvezp/quadcopter'

        self._uid = os.getuid()
        self._gid = os.getgid()

    def run(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--device=/dev/ttyUSB0',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--group-add=dialout',
               '--workdir={}'.format(self._build_dir),
              self._image,
              'make', 'upload']
        subprocess.check_call(cmd)
