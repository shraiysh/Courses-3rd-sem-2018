#!/usr/bin/env bash
#
# Assignment 2A test cases
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>
#
PASS="\e[042mPASS\e[0m"
FAIL="\e[041mFAIL\e[0m"

test_comparison() {
    if [[ `echo ${1} ${2} | ../bin/Assignment_2A` -eq $3 ]]; then
        echo -e " . . . ${PASS}"
    else
        echo -e " . . . ${FAIL}"
    fi
}

echo -e "\n>>>>> Testing Assignment 2A <<<<<\n"

printf "Expect 9000002 > 9000001"
test_comparison 9000002 9000001 1

printf "Expect 005 < 6 "
test_comparison 005 6 0

printf "Expect 500 > 007"
test_comparison 500 007 1

printf "Expect 0005 == 5"
test_comparison 0005 5 1

printf "Expect 00000076534444 < 86534444"
test_comparison 00000076534444 86534444 0

printf "Expect 00000090010020 > 00080001002"
test_comparison 00000090010020 00080001002 1

printf "Expect 999981132466 > 999981132465"
test_comparison 999981132466 999981132465 1

printf "Expect 00000000000000000098 < 00000101"
test_comparison 00000000000000000098 00000101 0

printf "Expect 00000101 > 00000000000000000098"
test_comparison 00000101 00000000000000000098 1

printf "Expect 010 > 00009"
test_comparison 010 00009 1

printf "Expect 9 < 10"
test_comparison 9 10 0

printf "Expect 4 < 05"
test_comparison 4 05 0

printf "Expect 0099 < 100"
test_comparison 0099 100 0

printf "Expect 747919191919100000002389 > 747191919191910000007389"
test_comparison 747919191919100000002389 747191919191910000007389 1

printf "Expect 99999999999999999999 == 99999999999999999999"
test_comparison 99999999999999999999 99999999999999999999 1

printf "Expect 0000000000000000000099999999999999999999 == 99999999999999999999"
test_comparison 0000000000000000000099999999999999999999 99999999999999999999 1

printf "Expect 1 < 2"
test_comparison 1 2 0

printf "Expect 1 == 1"
test_comparison 1 1 1

printf "Expect 10000000000001 == 000010000000000001"
test_comparison 10000000000001 000010000000000001 1

printf "Expect 0000100000000000001 < 100000000000002"
test_comparison 0000100000000000001 100000000000002 0

printf "Expect 0000999999999999999999999999 > 999999999999999999999998"
test_comparison 0000999999999999999999999999 999999999999999999999998 1

printf "Expect 0000987654321987654321987654321 > 000000098765432198765432198765432"
test_comparison 0000987654321987654321987654321 000000098765432198765432198765432 1

printf "Expect 5 > 3"
test_comparison 5 3 1

printf "Expect 3 == 3"
test_comparison 3 3 1

printf "Expect 3 < 5"
test_comparison 3 5 0

printf "Expect 001 == 0000001"
test_comparison 001 0000001 1

printf "Expect 1000000000000000 > 2000"
test_comparison 1000000000000000 2000 1

echo -e "\n>>>>> Complete <<<<<"
