import os
import subprocess

class FlightControllerBuilder(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'build', 'fc')
        self._fc_root = os.path.join(self._root, 'FlightController')
        self._toolchain = os.path.join(self._fc_root, 'cmake',
                                       'ArduinoToolchain.cmake')
        self._image = 'carlosgalvezp/quadcopter'

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
               self._image, 'cmake', self._fc_root,
               '-DCMAKE_TOOLCHAIN_FILE={}'.format(self._toolchain),
               '-DARDUINO_1_5=ON']
        subprocess.check_call(cmd)

    def _run_make(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
              self._image, 'make']
        subprocess.check_call(cmd)
