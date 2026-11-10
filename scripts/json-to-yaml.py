#!/usr/bin/env python3

import sys
import json
import yaml

input_json = sys.argv[1] if len(sys.argv) > 1 else None
output_yaml = sys.argv[2] if len(sys.argv) > 2 else None

data = None

if input_json is None:
    data = json.load(sys.stdin)
else:
    with open(input_json, 'r') as json_in:
        data = json.load(json_in)

if output_yaml is None:
    yaml.dump(data, sys.stdout, default_flow_style=False)
else:
    with open(output_yaml, 'wt') as yaml_out:
        yaml.dump(data, yaml_out, default_flow_style=False)

exit(0)

