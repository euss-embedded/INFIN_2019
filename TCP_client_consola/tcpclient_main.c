/***************************************************************************
                          main.c  -  client
                             -------------------
    begin                : lun feb  4 16:00:04 CET 2002
    copyright            : (C) 2002 by A. Moreno
    email                : amoreno@euss.es
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define REQUEST_MSG_SIZE	1024
#define REPLY_MSG_SIZE		500
#define SERVER_PORT_NUM		5001

void ImprimirMenu(void);
void comunicacio(char envio[],char bufferrecive[], char nameserver[]);


int main(int argc, char *argv[]){
	
	char envio[256];
	char nameserver[256];
	char bufferrecive[256];

	printf(" Introducir la dirección de servidor, ejemplo 127.0.0.1:\n");
	scanf("%s", nameserver);
	
	
	char input;

	ImprimirMenu();                             
	input = getchar();
	

	while (input != '7')
	{
		switch (input)
		{
			case '1':
				printf("Heu seleccionat l'opció 1\n");
				char tiempo[2];
				int i;
				int j;
				envio[0]="{";	
				envio[1]="M";	
				envio[6]="}" ;
				printf(" %s\n",envio);
					printf("introdueix: Parar=0 , Marcha = 1 \n");
					scanf("%s", &envio[2]);
					
					printf("introdueix el temps de mostreig màxim fins a 20s \n");
					scanf("%s", &tiempo);
					
					j=3;
					for(i=0;i==2;i++){
						
					envio[j]=tiempo[i];	
					j++;
					printf("%s\n",tiempo[i]);
					}
					
						/*if (tiempo< 10 && tiempo>=0){
						envio[4]=tiempo[1];
						envio[3]=0;
						
						
							}
							else{
							envio[3]=tiempo[0];
							envio[4]=tiempo[1];
						printf(" %s%s\n",envio[3],envio[4]);
						}*/
				
					printf("introdueix el número de mostres màxim fins a 9 \n");
					scanf("%s", &envio[5]);
				printf("%s\n",envio); 
				comunicacio(envio,bufferrecive,nameserver);
				
				ImprimirMenu();  
				                          
				break;
				
			case '2':
				printf("Heu seleccionat l'opció 2\n");
				
				comunicacio(envio,bufferrecive,nameserver);
					
				ImprimirMenu();                             
				break;
				
			case '3':
				printf("Heu seleccionat l'opció 3\n");
				
				comunicacio(envio,bufferrecive,nameserver);
					
				ImprimirMenu();                             
				break;
				
			case '4':
				printf("Heu seleccionat l'opció 4\n");
				
				comunicacio(envio,bufferrecive,nameserver);
					
				ImprimirMenu();                             
				break;
			case '5':
				printf("Heu seleccionat l'opció 5\n");
				
				comunicacio(envio,bufferrecive,nameserver);
					
				ImprimirMenu();                             
				break;
				
			case '6':
				printf("Heu seleccionat l'opció 6\n");
				
				comunicacio(envio,bufferrecive,nameserver);
					
				ImprimirMenu();                             
				break;
			
			case 0x0a: //Això és per enviar els 0x0a (line feed) que s'envia quan li donem al Enter
				break;
			default:
				printf("Opció incorrecta\n");	
				printf("He llegit 0x%hhx \n",input);
				break;
		}

		input = getchar();
	
}
return 0;
}	
void ImprimirMenu(void){
	printf("\n\nMenu:\n");
	printf("--------------------\n");
	printf("Tria la opció introduint el número corresponent\n");
	printf("\n");
	printf("1: Posar en marxa / parar l'adquisició\n");
	printf("2: Demanar mitjana\n");
	printf("3: Demanar màxim\n");
	printf("4: Demanar mínim\n");
	printf("5: Reset màxim i mínim\n");
	printf("6: Demanar comptador del nombre de mostres guardades\n");
	printf("7: Sortir\n");
	printf("\n");
	printf("--------------------\n");
}	
	
void comunicacio(char envio[],char bufferrecive[], char nameserver[]){
	
	struct sockaddr_in	serverAddr;
	char	    serverName[256]; //Adreça IP on est� el servidor
	int			sockAddrSize;
	int			sFd;
	int			mlen;
	int 		result;
	char		buffer[256];
	char		missatge[256];
	strcpy(serverName,nameserver);
	strcpy(buffer,bufferrecive);
	strcpy(missatge,envio);

	/*Crear el socket*/
	sFd=socket(AF_INET,SOCK_STREAM,0);

	/*Construir l'adreça*/
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = inet_addr(serverName);

	/*Conexió*/
	result = connect (sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	if (result < 0)
	{
		printf("Error en establir la connexió\n");
		exit(-1);
	}
	printf("\nConnexió establerta amb el servidor: adreça %s, port %d\n",	inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	/*Enviar*/
	strcpy(buffer,missatge); //Copiar missatge a buffer
	result = write(sFd, buffer, strlen(buffer));
	printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge);

	/*Rebre*/
	result = read(sFd, buffer, 256);
	printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);

	/*Tancar el socket*/
	close(sFd);
}
