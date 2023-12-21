"""debloater-eval package definition and install configuration"""
from imp import load_source
from pathlib import Path
from setuptools import find_packages, setup

pkginfo = load_source("pkginfo.version", "debloater_eval/version.py")
__version__ = pkginfo.__version__

root_dir = Path(__file__).parent
with open(root_dir / "requirements.txt", encoding="utf-8") as f:
    install_requires = [x.strip() for x in f.read().split("\n")]


setup(
    name="debloater-eval",
    version=__version__,
    python_requires=">=3.6",
    packages=find_packages(),
    install_requires=install_requires,
)
