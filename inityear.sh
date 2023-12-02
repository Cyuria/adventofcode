#!/bin/sh

year=$(date +%Y)
echo "The year is" $year
mkdir -p $year
for day in $(seq 1 25)
do
  dayname=$(printf "%02d" $day)
  echo "Creating for day" $dayname
  mkdir -p $year/$dayname
done

