#!/bin/bash

if [ "$1" == "--help" ] || [ $# -lt 2 ]; then
	echo -e "Uso: run.sh puerto args_server [valgrind]\n"
	exit -1
fi

server_host=$1
puerto=$2
modo=$4
max_clientes=100
server="server"
client="client"

if [ "$3" == "valgrind" ]; then
	pre_server='valgrind --gen-suppressions=all --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --db-attach=no --leak-check=full --leak-resolution=med --log-file=valgrind_server.out '
	pre_client='valgrind --gen-suppressions=all --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --db-attach=no --leak-check=full --leak-resolution=med --log-file=valgrind_client$n.out '
fi

echo "Probando caso en puerto $1 $2 en modo $4 $3"

shift
shift
shift
shift

echo -n "Running Server: "
mkfifo server-stdin
echo "$pre_server ./$server $puerto <>server-stdin >__server_stdout__ 2>__server_stderr__ &"
$pre_server ./$server $puerto <>server-stdin >__server_stdout__ 2> __server_stderr__ &
sleep 1
ps $! > /dev/null
server_status=$? 
if [ $! -gt 0 ] && [ $server_status -eq 0 ]; then
	echo -e "Server OK\n PID $!"
	server_pid=$!
else
	echo "Server Error"
	rm server-stdin
	exit 2
fi


for (( n=0; n < $max_clientes; n++ )); do
	if [ -f "netcat$n.in" ]; then	
		if [ "$modo" == "single" ]; then
			echo -n "Running Netcat $n: "
			echo "nc $server_host $puerto 0<netcat$n.in 1>netcat$n.out"
			eval nc $server_host $puerto 0<netcat$n.in 1>netcat$n.out
		else
			echo -n "Running Netcat $n: "
			echo "nc $server_host $puerto <>input_netcat$n >netcat$n.out &"
			mkfifo input_netcat$n
			eval nc $server_host $puerto <>input_netcat$n >netcat$n.out &
		fi
	fi
	if [ -f "client$n.in" ]; then
		if [ -f "client$n.args" ]; then
			client_args=$(cat client$n.args)
		fi
		if [ "$modo" == "single" ]; then
			echo -n "Running Client $n: "
			echo "$pre_client ./$client $server_host $puerto $client_args 0<client$n.in 1>client$n.out"
			eval $pre_client ./$client $server_host $puerto $client_args 0<client$n.in 1>client$n.out
		else
			echo -n "Running Client $n: "
			echo "$pre_client ./$client $server_host $puerto $client_args <>input_cliente$n >client$n.out &"
			mkfifo input_cliente$n
			eval $pre_client ./$client $server_host $puerto $client_args <>input_cliente$n >client$n.out &
		fi
	fi
done

if [ "$modo" == "multiple" ]; then
	for (( n=0; n < $max_clientes; n++ )); do
		if [ -f "netcat$n.in" ]; then
			echo "Sending input - Netcat $n"
			eval cat netcat$n.in > input_netcat$n
		fi
		if [ -f "client$n.in" ]; then
			echo "Sending input - Cliente $n"
			eval cat client$n.in > input_cliente$n
		fi
	done
	sleep 1
	for (( n=0; n < $max_clientes; n++ )); do
	  	if [ -f "netcat$n.in" ]; then
			echo "Closing input - Netcat $n"
			rm input_netcat$n
		fi
	  	if [ -f "client$n.in" ]; then
			echo "Closing input - Cliente $n"
			rm input_cliente$n
		fi
	done
fi

echo -n "Terminando server..."
echo -e "q\n" >> server-stdin
sleep 1
rm -f server-stdin
if [ $? -eq 0 ]; then
	echo "Server detenido OK"
else
	echo "Server ERROR"
	kill -9 $server_pid
fi
