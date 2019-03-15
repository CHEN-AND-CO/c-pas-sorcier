
set datafile separator ','

stats 'trace.txt' using 0:2 name 'A'

set xrange [A_records + A_outofrange-500:A_records + A_outofrange]
set yrange [-5:40]

plot 'trace.txt' using 0:1 with lines title "setpoint", \
     'trace.txt' using 0:2 with lines title "current", \
     'trace.txt' using 0:3 with lines title "p", \
     'trace.txt' using 0:4 with lines title "i", \
    #  'trace.txt' using 0:5 with lines title "d", \
    #  'trace.txt' using 0:6 with lines title "output"

pause 0.1
reread
