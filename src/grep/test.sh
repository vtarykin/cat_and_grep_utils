# 1. An option with one file.
options="evinclhs"
test_count=1
for (( i=0; i<${#options}; i++ ));
do
    grep -"${options:$i:1}" is test.txt > original.txt
    ./s21_grep -"${options:$i:1}" is test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR with flag ${options:$i:1} in test $test_count"
    else
	echo "Test $test_count with flag ${options:$i:1} completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 2. An option witn a couple of files. 
for (( i=0; i<${#options}; i++ ));
do
    grep -"${options:$i:1}" is test.txt gorillaz.txt > original.txt
    ./s21_grep -"${options:$i:1}" is test.txt gorillaz.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR with flag ${options:$i:1} in test $test_count"
    else
	echo "Test $test_count with flag ${options:$i:1} completed succesfully"
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done
