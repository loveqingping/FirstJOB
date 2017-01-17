
gcc   -g3 -Wall demo.c -I/usr/local/curl/include -L /usr/local/curl/lib -lcurl -lavro -o demo 

#gcc caculate.c  -shared  -fPIC -o libcaculate.so
#gcc main.c -o main -L /root/wkp/dlldemo -lcaculate 
#gcc call_main.c -o call_main -ldl
