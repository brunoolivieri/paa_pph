#!/bin/bash
$(find ./data/ -name "*" -exec ./main 0 {} \; ) 
$(find ./data/ -name "*" -exec ./main 1 {} \; ) 
$(find ./data/ -name "*" -exec ./main 2 {} \; ) 

#./bin/Debug/paa 3 $(find ./data/ -name "*.dat")
