#!/bin/bash
  gcc -Wall -O2 -o tests mst2.c
  for i in {1..30}
  do
 	echo "Testing testcase $i"     
      time -p  ./tests <testcases/input$i.txt > a.txt 
      if (diff  -b testcases/output$i.txt a.txt )  then
        txtrst=$(tput sgr0) 
	txtgrn=$(tput setaf 2) # Green
	echo "${txtgrn}PASS!${txtrst}"
      else 
        echo "FAILED!"
	txtrst=$(tput sgr0)
        txtred=$(tput setaf 1)
        echo "${txtred}Different!${txtrst}"
      fi
	rm a.txt
  done
  rm tests
