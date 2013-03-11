
gcc -Wall -O3 -o race2  race.c
  for i in {1..20}
  do
 	echo "Testing testcase $i"     
      time   ./race2 <racing/in$i.txt > a.txt
      if (diff  -b racing/out$i.txt a.txt )  then
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
	rm race2
