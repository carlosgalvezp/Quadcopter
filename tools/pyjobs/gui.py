import os
import subprocess

class GUIBuilder(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'GUI', 'build')
        self._pro_path = os.path.join(self._root, 'GUI', 'src', 'CriusGUI.pro')

        self._image = 'carlosgalvezp/qt-dev'

        self._uid = os.getuid()
        self._gid = os.getgid()

        if not os.path.isdir(self._build_dir):
            os.makedirs(self._build_dir)

    def run(self):
        self._run_qmake()
        self._run_make()

    def _run_qmake(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
              self._image,
              'qmake', self._pro_path, '-spec', 'linux-g++-64']
        subprocess.check_call(cmd)


    def _run_make(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true',
               '--volume={}:{}'.format(self._root, self._root),
               '--user={}:{}'.format(self._uid, self._gid),
               '--workdir={}'.format(self._build_dir),
              self._image,
              'make']
        subprocess.check_call(cmd)


class GUIRunner(object):
    def __init__(self):
        self._this_path = os.path.dirname(os.path.realpath(__file__))
        self._root = os.path.abspath(os.path.join(self._this_path, '..', '..'))
        self._build_dir = os.path.join(self._root, 'GUI', 'build')
        self._image = 'carlosgalvezp/qt-dev'

        self._uid = os.getuid()
        self._gid = os.getgid()

        self._device = '/dev/ttyUSB0'

    def run(self):
        cmd = ['docker', 'run',
               '--rm=true',
               '--tty=true']

        if os.path.exists(self._device):
            cmd.extend('--device={}'.format(self._device))
        else:
            print('WARNING: {} not found. ' \
                  'Please connect the Crius board'.format(self._device))

        cmd.extend(['--volume={}:{}'.format(self._root, self._root),
                    '--user={}:{}'.format(self._uid, self._gid),
                    '--group-add=dialout',
                    '--env=DISPLAY',
                    '--volume=/tmp/.X11-unix:/tmp/.X11-unix',
                    '--workdir={}'.format(self._build_dir),
                    self._image,
                    './CriusGUI'])

        subprocess.check_call(cmd)
