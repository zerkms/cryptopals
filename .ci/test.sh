#!/bin/bash

BUILD_DIR=$(readlink -f ./build)
FIXTURES_DIR=$(readlink -f ./tests/fixtures)

cd $FIXTURES_DIR
$BUILD_DIR/cryptopals_tests -d yes
