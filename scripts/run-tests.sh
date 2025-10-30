#!/bin/bash

prj_path=$(dirname $0)/..

types=(3s 4s lt o2)
ports=(ble uart)
conns=(api mqtt)

test_dir=$prj_path/tests/gen
conf_dir=$prj_path/configs

ESPHOME_DATA_DIR=$prj_path/.build.nosync/esphome-tests

for type in "${types[@]}"; do
  for port in "${ports[@]}"; do
    for conn in "${conns[@]}"; do
      conf=$test_dir/tion-$type-$port-$conn.yaml
      if [ -f "$conf" ]; then
        esphome compile $conf || exit
      fi
    done
  done
done
