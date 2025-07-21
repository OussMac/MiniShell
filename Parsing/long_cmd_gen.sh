#!/bin/bash

cmd=""

part="(echo start && echo middle || echo fail) | grep start && (echo foo > file.txt || cat < file.txt) | (echo end >> file.txt && cat file.txt || echo retry) && (echo done && (echo nested || echo fallback)) | cat file.txt"

# Repeat 'part' 30 times (each part roughly ~20 tokens)
for i in {1..5}
do
  if [ -z "$cmd" ]; then
    cmd="$part"
  else
    # Mix AND and OR between parts to increase complexity
    if (( i % 2 == 0 )); then
      cmd="$cmd && $part"
    else
      cmd="$cmd || $part"
    fi
  fi
done

echo "$cmd" > long_cmd.txt
