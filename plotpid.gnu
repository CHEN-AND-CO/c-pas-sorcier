
stats 'pid.log' using 0:1 name 'A'


set xrange [A_records + A_outofrange-500:A_records + A_outofrange]
set yrange [-20:105]
set datafile separator ','

plot 'pid.log' using 0:1 with lines title "setpoint", \
     'pid.log' using 0:2 with lines title "current", \
     'pid.log' using 0:3 with lines title "p", \
     'pid.log' using 0:4 with lines title "i", \
     'pid.log' using 0:5 with lines title "d", \
     'pid.log' using 0:6 with lines title "output"

pause 0.1
reread
