#!/bin/bash

sbatch 	--partition=general \
		-N 1 \
		--mem=16g \
		--time="2-00:00:00" \
		--job-name="toggle-prm" \
		--wrap="./benchmark.sh"
