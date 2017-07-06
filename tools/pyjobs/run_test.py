import os
import subprocess

class FlightControllerTestRunner(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'build', 'test')
        self._fc_root = os.path.join(self._root, 'FlightController')

        self._image = 'carlosgalvezp/cpp-dev'

        self._uid = os.getuid()
        self._gid = os.getgid()

    def run(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
               self._image, './test/test1']
        subprocess.check_call(cmd)
