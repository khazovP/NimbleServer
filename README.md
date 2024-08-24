# NimbleServer
A very flexible, lightweight and high performance HTTP server library based on [libev] and [http-parser] for Embedded Linux.

# Features
* Lightweight and high performance
* Use [libev] as its event backend
* Support HTTPS - OpenSSL, mbedtls and CyaSSl(wolfssl)
* Support IPv6
* Support CGI
* Support plugin
* Support upload large file
* Support HTTP range requests
* Support multi-process model - The same multi-process model as Nginx
* Flexible - you can easily extend your application to have HTTP/HTTPS services
* Code structure is concise and understandable, also suitable for learning

# Dependencies
* [libev] - A full-featured and high-performance event loop
* [http-parser] - A high performance parser for HTTP messages written in C
* [mbedtls] - If you choose mbedtls as your SSL backend
* [wolfssl] - If you choose wolfssl as your SSL backend
* [openssl] - If you choose openssl as your SSL backend

# Benchmark
## Nginx

	$ wrk -t4 -c400 -d10s http://localhost:80/test.html
	Running 10s test @ http://localhost:80/test.html
	4 threads and 400 connections
	Thread Stats   Avg      Stdev     Max   +/- Stdev
		Latency     3.54ms    7.32ms 224.58ms   93.30%
		Req/Sec    40.63k    12.49k   96.29k    74.50%
	1622012 requests in 10.05s, 385.09MB read
	Requests/sec: 161390.39
	Transfer/sec:     38.32MB

## NimbleServer

	$ wrk -t4 -c400 -d10s http://localhost:8080/test.html
	Running 10s test @ http://localhost:8080/test.html
	4 threads and 400 connections
	Thread Stats   Avg      Stdev     Max   +/- Stdev
		Latency     2.12ms    3.01ms  31.30ms   89.26%
		Req/Sec    70.87k    12.53k  142.54k    79.75%
	2826394 requests in 10.05s, 547.18MB read
	Requests/sec: 281328.83
	Transfer/sec:     54.46MB

# Build

	~/NimbleServer/$ mkdir build && cd build
	~/NimbleServer/build$ cmake ..
	~/NimbleServer/build$ make

# Run Example	
Run

	~/NimbleServer/build$ ./example/simple_server -v -a :8080
	
Then use the curl to test

	$ curl 'http://127.0.0.1:8000/echo' -v

