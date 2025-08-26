#!/bin/bash
set -euo pipefail
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

make clean
rm -f "$PROJECT_DIR*.nds" "$PROJECT_DIR*.elf"