target:
	gcc -Wall -g -std=c11 -v ./src/echo_server.c -o ./build/server
	gcc -Wall -g -std=c11 -v ./src/echo_client.c -o ./build/client

clean:
	rm ./build/*
