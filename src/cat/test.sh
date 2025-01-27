single_opts="benstvET"
double_opts="bnbsbebtbvbEbTnsnentnvnEnTsestsvsEsTeteveTvE"
triple_opts="bnebnsbnebntbnvbnTbnEnsenstnsvnsTnsEsetsevseTsEvevTEvT"
quadr_opts="bnesbnetbnevbnETnvETnestnesTnesEseTEsTvE"
five_opts="bnestbnesTbnEsTbsvETnsvETnsvET"
test_count=1

# 1. Tests to check cat util with 1 option
for (( i=0; i<${#single_opts}; i++ ));
do
    cat -"${single_opts:$i:1}" test.txt > original.txt
    ./s21_cat -"${single_opts:$i:1}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flag ${single_opts:$i:1} in test $test_count"
    else
	echo "Test $test_count with flag ${single_opts:$i:1} completed succesfully"  
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 2. Tests to check cat util with 2 option
for (( i=0; i<${#double_opts}; i+=2 ));
do
    cat -"${double_opts:$i:2}" test.txt > original.txt
    ./s21_cat -"${double_opts:$i:2}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags ${double_opts:$i:2} in test $test_count"
    else
	echo "Test $test_count with flags ${double_opts:$i:2} completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done


# 3. Tests to check cat util with 3 option
for (( i=0; i<${#triple_opts}; i+=3 ));
do
    cat -"${triple_opts:$i:3}" test.txt > original.txt
    ./s21_cat -"${triple_opts:$i:3}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags ${triple_opts:$i:3} in test $test_count"
    else
	echo "Test $test_count with flags ${triple_opts:$i:3} completed succesfully" 
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 4. Tests to check cat util with 4 option
for (( i=0; i<${#quadr_opts}; i+=4 ));
do
    cat -"${quadr_opts:$i:4}" test.txt > original.txt
    ./s21_cat -"${quadr_opts:$i:4}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags ${quadr_opts:$i:4} in test $test_count"
    else
	echo "Test $test_count with flags ${quadr_opts:$i:4} completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 5. Tests to check cat util with 5 option
for (( i=0; i<${#five_opts}; i+=5 ));
do
    cat -"${five_opts:$i:1}" test.txt > original.txt
    ./s21_cat -"${five_opts:$i:1}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags ${five_opts:$i:5} in test $test_count"
    else
	echo "Test $test_count with flags ${five_opts:$i:5} completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 6. Test to check all options handling
    cat -"bnstev" test.txt > original.txt
    ./s21_cat -"bnstev"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags bnstev in test $test_count"
    else
	echo "Test $test_count with flags bnstev completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt

# 7. Tests to check cat util with long options
for str in number number-nonblank squeeze-blank;
do
    cat --"${str}" test.txt > original.txt
    ./s21_cat --"${str}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flag $str in test $test_count"
    else
        echo "Test $test_count with flag $str completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

