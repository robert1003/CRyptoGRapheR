#!/bin/bash

cpp -dD -P -fpreprocessed $1 | tr -d '[:space:]'| md5sum |cut -c-6
