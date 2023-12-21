import yaml
import shlex
import subprocess
import os
import sys
import tempfile
import re

import benchmark_binaries

def run(args):
    if type(args) is str:
        args = shlex.split(args)
    print(f"Executing {args}")
    subprocess.run(args, check=True)

benchmark_full = sys.argv[1] # like: medium/memcached-1.6.18
benchmark = os.path.basename(benchmark_full) # like: memcached-1.6.18
benchmark_simple = re.sub("-[\d\.\-]+$", "", benchmark) # like: memcached
complexity = os.path.basename(os.path.dirname(benchmark_full)) # like: medium
container = sys.argv[2]


def oracle_cmd(record):
    """
    Generate the command used to run the oracle.  If the benchmark is low 
    complexity, the record parameter is ignored.
    """
    if complexity == "low":
        return "./oracle.sh"

    ports = {
        "bftpd-6.1": 20000,
        "memcached-1.6.18": 25000,
        "lighttpd-1.4": 30000,
        "nginx-1.23.3": 35000,
    }
    if benchmark in ports:
        port_args = f"--port_start {ports[benchmark]} --processes 8"
    else:
        port_args = ""
    if record:
        record = "--record"
        sut_location = f"/host/benchmarks/{benchmark_full}/binaries/64/{binary_basename}"
    else:
        sut_location = os.path.join("./", binary)
        record = ""

    # hack to get memcached's tests working
    memcached_user = ""
    if benchmark == "memcached-1.6.18":
        memcached_user = "runuser -u memcached --"

    return (
        f"{memcached_user} /bin/bash -c \"source /chisel_env/bin/activate && "
        f"python3 /host/tool-debloating-specs/chisel_oracle.py {record} "
        f"{port_args} {sut_location} "
        f"{complexity}.{benchmark_simple}.oracle_{benchmark_simple}\""
    )


# Get the benchmark data
data = benchmark_binaries.benchmark_binaries()
benchmark_data = benchmark_binaries.expand_variables(
    data[benchmark_full],
    benchmark_binaries.Arch._64,
    benchmark_binaries.make_variables(benchmark_binaries.Arch._64, cfi=False)
)
binary = benchmark_data["binaries"][0]
binary_basename = os.path.basename(binary)

# Execute the benchmark init commands in the container
init = benchmark_data.get("init", [])
working_directory = f"/chisel/{benchmark}"
env = ""
for e,v in benchmark_data["env"].items():
    env += f"--env {e}=\"{v}\" "
for cmd in init:
    run(f"docker exec {env} -w {working_directory} {container} {cmd}")

# Copy the input files into position
input_files_dir_host = f"./tool-debloating-specs/{complexity}/input_files/{benchmark_simple}/."
input_files_dir = os.path.join("/host", input_files_dir_host)
if complexity == "low" and os.path.exists(input_files_dir_host):
    copy_cmd = (
        f"docker exec -w {working_directory} {container} "
        f"cp -rn {input_files_dir} ./"
    )
else:
    copy_cmd = (
        f"docker exec -w {working_directory} {container} "
        f"cp -r /host/tool-debloating-specs/{complexity}/input_files /input_files"
    )
run(copy_cmd)

# Copy the oracle into position for the low benchmarks
if complexity == "low":
    run(
        f"docker exec -w {working_directory} {container} "
        f"cp /host/tool-debloating-specs/low/{benchmark_simple}/oracle.sh ./"
    )

# Generate the known good values for the oracle.
if complexity != "low":
    record_cmd = oracle_cmd(
        record=True,
    )
    full_record_cmd = f"docker exec -w {working_directory} {container} {record_cmd}"
    run(full_record_cmd)

# Generate the build script
with tempfile.NamedTemporaryFile(mode="w") as tmp:
    cmds = benchmark_data["pre-build"] + benchmark_data["build"]
    tmp.write("#!/bin/bash\n")
    for cmd in cmds:
        tmp.write(cmd + "\n")
    tmp.flush()
    run(f"docker cp {tmp.name} {container}:{working_directory}/build.sh")
run(f"docker exec {container} chmod +x {working_directory}/build.sh")

# Generate the spec if it doesn't exist
oracle_cmd = oracle_cmd(record=False)
spec_path_host = f"./tool-debloating-specs/{complexity}/{benchmark_simple}/chisel-2-spec.yml"
spec_path = os.path.join("/host", spec_path_host)
print(f"Does it exist? ?? ?? ? ? {spec_path}")
if not os.path.exists(spec_path_host):
    print("building spec")
    spec_build_cmd = [
        "/bin/bash",
        "-c",
        f"source /chisel_env/bin/activate && python3 /host/build-binaries/gen-chisel-2-spec.py {benchmark_full} '{oracle_cmd}' > {spec_path}"
    ]
    spec_cmd = ["docker", "exec", "-w", working_directory, container] + spec_build_cmd
    run(spec_cmd)
run(f"docker exec -w {working_directory} {container} cp {spec_path} ./")
