#!/bin/bash
set -e

THIS_DIR=$(dirname "$0")

$THIS_DIR/setup_docker.sh
$THIS_DIR/setup_arduino.sh
