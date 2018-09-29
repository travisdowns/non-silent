if [ -z $1 ]; then
    echo "you must provide the input file"
    exit 1
fi

FILE=$1
EVENTS="l2_lines_in.all l2_lines_out.silent l2_lines_out.non_silent"

grepout() {
    egrep $1 $FILE | egrep -o "^[0-9]*"
}

for e in $EVENTS; do
#    echo "Processing event $e"
    TFILE=$e.tmpxx
    echo $e > $TFILE
    grepout $e >> $TFILE
done

paste -d, *.tmpxx

rm *.tmpxx