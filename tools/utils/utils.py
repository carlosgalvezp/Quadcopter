import os
import shutil

def maybe_remove_path(path):
    if os.path.exists(path):
        shutil.rmtree(path)
