import os
import subprocess

class FlightControllerTestBuilder(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'build', 'test')
        self._fc_root = os.path.join(self._root, 'FlightController')

        self._image = 'carlosgalvezp/cpp-dev'

        self._uid = os.getuid()
        self._gid = os.getgid()

    def run(self):
        # Create directory if it doesn't exist
        if not os.path.exists(self._build_dir):
            os.makedirs(self._build_dir)

        self._run_cmake()
        self._run_make()

    def _run_cmake(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
               self._image, 'cmake', self._fc_root]
        subprocess.check_call(cmd)

    def _run_make(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
              self._image, 'make', 'VERBOSE=1']
        subprocess.check_call(cmd)
