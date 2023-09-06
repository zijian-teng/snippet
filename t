#!/bin/bash

LAST_IP="53.244.42.180"

if [ -z "$1" ]; then
  IP=$LAST_IP
else
  IP="53.244.42.$1"
  # Update the script with the new IP address
  sed -i "s/LAST_IP=\"$LAST_IP\"/LAST_IP=\"$IP\"/" "$0"
fi

ssh root@"$IP"
