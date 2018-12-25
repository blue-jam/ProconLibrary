import os
import glob

CONFIG_FILE = "DATASET"
TEST_DIR = "test"
AOJ_PREFIX = "aoj"
AOJ_PROBLEM_URL = ""

cwd = os.getcwd()
downloader = "oj"


def aojdataset(problem_id, prefix="", num=None):
    cwd = os.getcwd()
    dirname = "{0}{1}".format(prefix, problem_id)

    filepattern = os.path.join(cwd, dirname, TEST_DIR, "*.in")
    if len(glob.glob(filepattern)):
        return None

    os.chdir(os.path.join(cwd, dirname))

    aoj_url = "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id={0}".format(problem_id)
    os.system("{0} download {1} --system 2> /dev/null".format(downloader, aoj_url))

    out_file_pattern = os.path.join(cwd, dirname, TEST_DIR, "*.out")
    for out_filename in glob.glob(out_file_pattern):
        diff_filename = out_filename.replace(".out", ".diff")
        os.rename(out_filename, diff_filename)

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
