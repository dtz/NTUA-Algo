
gcc -Wall -O3 -o cup  cup.c
  for i in {1..14}
  do
 	echo "Testing testcase $i"     
      time   ./cup <football/in$i.txt > a.txt 
      if (diff  -b football/out$i.txt a.txt )  then
        txtrst=$(tput sgr0) 
	txtgrn=$(tput setaf 2) # Green
	echo "${txtgrn}PASS!${txtrst}"
      else 
	txtrst=$(tput sgr0)
        txtred=$(tput setaf 1)
        echo "${txtred}FAIL!${txtrst}"
      fi
	rm a.txt
  done
	rm cup
