import subprocess

def run_cmd(cmd):
    result = subprocess.run(cmd, stdout=subprocess.PIPE)
    print(result.stdout.decode('utf-8'))
    return result.returncode

def didItPass(exit_code):
    if exit_code == 0:
        return "SUCCESS"
    else:
        return "FAILED"

# script
build_leonardo_cmd = ['pio', 'run', '-e', 'leonardo']
test_host_cmd = ['pio', 'test', '-e', 'host']
test_leonardo_cmd = ['pio', 'test', '-e', 'leonardo']
build_leonardo = " ".join(build_leonardo_cmd)
test_host = " ".join(test_host_cmd)
exit_codes = {build_leonardo: 0, test_host: 0}

exit_codes[build_leonardo] = run_cmd(build_leonardo_cmd)
exit_codes[test_host] = run_cmd(test_host_cmd)

print("build of 'leonardo' environment: " + didItPass(exit_codes[build_leonardo]))
print("test in 'host' environment: " + didItPass(exit_codes[test_host]))
