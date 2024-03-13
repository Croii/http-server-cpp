#!/bin/bash

./your_server.sh &
sleep 1

response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:4221)

if [ "$response" -eq 200 ]; then
    echo "Test passed. HTTP response code is $response"
else
    echo "Test failed. HTTP response code is $response"
fi