#!/bin/bash

for input in *.in; do
    output=${input%in}out
    echo "$output does not exist. Generating it now..."
    touch $output
done

