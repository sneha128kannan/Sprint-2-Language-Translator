run_server: server.o delete.o write.o modify.o
	gcc ../obj/server.o ../obj/delete.o ../obj/write.o ../obj/modify.o -o ../src/server

run_client: client.o 
	gcc ../obj/client.o -o ../src/client

client.o: ../src/client.c
	gcc -o ../obj/client.o -c ../src/client.c

server.o: ../src/server.c
	gcc -o ../obj/server.o -c ../src/server.c

delete.o: ../src/delete.c
	gcc -o ../obj/delete.o -c ../src/delete.c

write.o: ../src/write.c
	gcc -o ../obj/write.o -c ../src/write.c

modify.o: ../src/modify.c
	gcc -o ../obj/modify.o -c ../src/modify.c

clean:
	@echo"cleaning files....."
	rm ../obj/server.o ../obj/delete.o ../obj/write.o ../obj/modify.o ../obj/client.o
