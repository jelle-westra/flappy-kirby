#!/bin/bash
set -euo pipefail
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

/bin/bash "$PROJECT_DIR/clean.sh"
docker run --rm -it \
  -v "$PROJECT_DIR":/flappy-kirby \
  -w /flappy-kirby \
  devkitpro/devkitarm:20250728 make

open "$PROJECT_DIR/flappy-kirby.nds"