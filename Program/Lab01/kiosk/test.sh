#!/bin/bash
  gcc -Wall -o kiosk1 kiosk.c
  for i in {1..31}
  do
 	echo "Testing testcase $i"     
      time -p  ./kiosk1 <testcases/input$i.txt > a.txt 
      if (diff  -b testcases/output$i.txt a.txt )  then
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

