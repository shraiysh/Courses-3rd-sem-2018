sum=0
for i in $(seq 1 $1);
do
   sum=`expr $sum + $i`;
done
echo $sum
