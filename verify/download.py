import os
import glob

CONFIG_FILE = "DATASET"
TEST_DIR = "test"
AOJ_PREFIX = "aoj"

cwd = os.getcwd()
downloader = os.path.join(cwd, "aojsetdownload.sh")


def aojdataset(problem_id, prefix="", num=None):
    cwd = os.getcwd()
    dirname = "{0}{1}".format(prefix, problem_id)

    filepattern = os.path.join(cwd, dirname, TEST_DIR, "*.in")
    if len(glob.glob(filepattern)):
        return None

    os.chdir(os.path.join(cwd, dirname, TEST_DIR))

    if num is None:
        os.system("{0} {1}".format(downloader, problem_id))
    else:
        os.system("{0} {1} {2}".format(downloader, problem_id, num))
    os.chdir(cwd)


for d in os.listdir(cwd):
    if not os.path.isdir(os.path.join(cwd, d)):
        continue
    if not os.path.exists(os.path.join(cwd, d, CONFIG_FILE)):
        continue
    os.chdir(d)
    with open(CONFIG_FILE, "r") as f:
        s = f.read()
        exec(compile(s, os.path.join(d, CONFIG_FILE), 'exec'))
    os.chdir(cwd)
