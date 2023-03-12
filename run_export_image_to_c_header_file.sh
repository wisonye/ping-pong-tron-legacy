#!/bin/sh
cd temp_build; clear; make && ./export_image_to_c_header_file $1 $2; cd ..
