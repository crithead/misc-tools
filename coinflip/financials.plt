NAME = "0008"
set title "1 Year (250 days)"
set term png size 800, 600
#set term png size 1600, 1200
set output NAME.".png"
set style line 1 linecolor rgb "navy"
set grid
plot "financials_".NAME.".data" with financebars ls 1 title NAME
#plot "financials_".NAME.".data" with candlesticks ls 1 title NAME

