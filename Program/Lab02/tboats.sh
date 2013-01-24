#!/bin/bash
  gcc -Wall -o boat boats.c
  for i in {1..12}
  do
 	echo "Testing testcase $i"     
      time -p  ./boat <boats/input$i.txt > a.txt 
      if (diff  -b boats/output$i.txt a.txt )  then
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
