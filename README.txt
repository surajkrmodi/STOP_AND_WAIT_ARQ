/*  STOP AND WAIT ARQ PROTOCOL  USING UDP PROTOCOL 

IN THE SAMPLE EXECUTTION METHOD "4000" IS THE PORT NUMBER BUT IT CAN BE ANY 4 DIGIT NUMBER LIKE "4005" */

// TO EXECUTE THE PROGRAM , FIRST RUN SERVER PROGRAM  

    gcc saw_server.c -o saw_server
    ./saw_server 4000

// THEN RUN CLIENT PROGRAM
    
    gcc saw_client.c -o saw_client
    ./saw_client 4000

***** THANK YOU *****
