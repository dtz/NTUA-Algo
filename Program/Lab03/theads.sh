#!/bin/bash
  gcc -Wall -O2 -o heads head.c
  for i in {1..14}
  do
 	echo "Testing testcase $i"     
      time -p  ./heads <headquarters/input$i.txt > a.txt 
      if (diff  -b headquarters/output$i.txt a.txt )  then
        txtrst=$(tput sgr0) 
	txtgrn=$(tput setaf 2) # Green
	echo "${txtgrn}Same!${txtrst}"
      else 
        echo "Different!"
	txtrst=$(tput sgr0)
        txtred=$(tput setaf 1)
        echo "${txtred}Different!${txtrst}"
      fi
	rm a.txt
  done
	rm heads
