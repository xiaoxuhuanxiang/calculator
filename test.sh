#!/usr/bin/expect
set timeout 5
spawn ./calculator/calculator

# only plus
expect {
    ">" {send "1+2+3+4;\r"}
}

# mutiply, conisder priority
expect {
    ">" {send "1+2*3+4;\r"}
}

# mutiply, ()
expect {
    ">" {send "(1+2)*3+4;\r"}
}

# mutiply, conisder priority, first 0
expect {
    ">" {send "(01+2)*03+4;\r"}
}
# + * /, conisder priority, first 0, ()
expect {
    ">" {send "1/2+3*5+(012.53+09.8/02)*6;\r"}
}
# + - * /, conisder priority, first 0, (), space, tab
expect {
    ">" {send "1/2+3*5-	(012.53+ 09.8/02)*6;\r"}
}

# one sentence split to two lines.
# + - * /, conisder priority, first 0, (), space, tab
expect {
    ">" {send "1/2+3*5\r"}
}
expect {
    ">" {send " -	(012.53+ 09.8/02)*6;\r"}
}

# one sentence and a half in one line
expect {
    ">" {send "1+2+4-6*2; 1+3+5-9*7\r"}
}

expect {
    "> 1+3+5-9*7" {send ""}; #The halfline will be print again by the calculator
}

expect {
    ">" {send " -8;\r"}
}

# blank line
expect {
    ">" {send "\r"}
}

expect {
    ">" {send "1+3;\r"};
}
#exit
expect {
    ">" {send "quit;\r"}
}

expect eof
