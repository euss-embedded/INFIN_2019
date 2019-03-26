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
	
	char envio[8];
	char nameserver[100];
	char bufferrecive[12];

	printf(" Introducir la dirección de servidor, ejemplo 127.0.0.1:\n");
	scanf("%s", nameserver);
	
	
	char input;

	ImprimirMenu();                             
	input = getchar();
	

	while (input != '7')
	{
		memset( envio, '#', 7 );
		envio[8] = 0;
		switch (input)
		{
			case '1':
				printf("Heu seleccionat l'opció 1\n");
				char tiempo[3];
				
				envio[0]='{';	
				envio[1]='M';	
			
					printf("introdueix: Parar=0 , Marcha = 1 \n");
					scanf("%s", &envio[2]);
					
					printf("introdueix el temps de mostreig màxim fins a 20s \n");
					scanf("%s", &tiempo[0]);
					
						
					
						if (tiempo[1]==0){
						envio[3]='0';
						envio[4]=tiempo[0];
						
							}
							else{
							envio[3]=tiempo[0];
							envio[4]=tiempo[1];
						
							}
					
					printf("introdueix el número de mostres màxim fins a 9 \n");
					scanf("%s", &envio[5]);
					
				envio[6]='}';
				
				printf("%s\n",envio);
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				if (bufferrecive[2]==0){
					printf("Conexió OK\n");
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR parametres\n");
				}
				ImprimirMenu();  
				                          
				break;
				
			case '2':
				printf("Heu seleccionat l'opció 2\n");
				envio[0]='{';	
				envio[1]='U';	
				envio[2]='}';
				printf("%s\n",envio);
		
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				if (bufferrecive[2]==0){
					printf("Conexió OK\n");
					
			
				char MITJANA[5];

						MITJANA[0]=bufferrecive[4];
						MITJANA[1]=bufferrecive[5];
						MITJANA[2]=bufferrecive[6];
						MITJANA[3]=bufferrecive[7];
						MITJANA[4]=bufferrecive[8];
						
				printf("la mitjana es:%s\n",MITJANA);
				
					
					
			
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol mitjana\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR paràmetres mitjana\n");
				}
					
				ImprimirMenu();                             
				break;
				
			case '3':
				printf("Heu seleccionat l'opció 3\n");
				envio[0]='{';	
				envio[1]='X';	
				envio[2]='}';
				printf("%s\n",envio);
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				if (bufferrecive[2]==0){
					printf("Conexió OK\n");
					
			
				char MAXIM[5];

						MAXIM[0]=bufferrecive[4];
						MAXIM[1]=bufferrecive[5];
						MAXIM[2]=bufferrecive[6];
						MAXIM[3]=bufferrecive[7];
						MAXIM[4]=bufferrecive[8];
				printf("la temperatura màxima és:%s\n",MAXIM);
				
					
					
			
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol màxim\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR paràmetres màxim\n");
				}
				
				
				
				
					
				ImprimirMenu();                             
				break;
				
			case '4':
				printf("Heu seleccionat l'opció 4\n");
				envio[0]='{';	
				envio[1]='Y';	
				envio[2]='}';
				printf("%s\n",envio);
				
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				if (bufferrecive[2]==0){
					printf("Conexió OK\n");
					
			
				char MINIM[5];

						MINIM[0]=bufferrecive[4];
						MINIM[1]=bufferrecive[5];
						MINIM[2]=bufferrecive[6];
						MINIM[3]=bufferrecive[7];
						MINIM[4]=bufferrecive[8];
				printf("la temperatura mínima és:%s\n",MINIM);
				
					
					
			
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol mínim\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR paràmetres mínim\n");
				}
				
				
			
			
					
				ImprimirMenu();                             
				break;
			case '5':
				printf("Heu seleccionat l'opció 5\n");
				envio[0]='{';	
				envio[1]='R';	
				envio[2]='}';
				printf("%s\n",envio);
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				
				if (bufferrecive[2]==0){
					printf("Reset OK\n");
					
					
					
		
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol reset\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR paràmetres reset\n");
				}
				
				
				
					
				ImprimirMenu();                             
				break;
				
			case '6':
				printf("Heu seleccionat l'opció 6\n");
				envio[0]='{';	
				envio[1]='B';	
				envio[2]='}';
				printf("%s\n",envio);
				
				comunicacio(envio,bufferrecive,nameserver);
				printf("%s\n",bufferrecive);
				
				
				if (bufferrecive[2]==0){
					printf("Conexió OK\n");
				char comptador[4];

						comptador[0]=bufferrecive[4];
						comptador[1]=bufferrecive[5];
						comptador[2]=bufferrecive[6];
						comptador[3]=bufferrecive[7];
						
				printf("%s\n",comptador);
				
					
					
				}
				else if(bufferrecive[2]==1){
					printf("ERROR protocol comptador\n");
				}
				else if(bufferrecive[2]==2){
					printf("ERROR paràmetres comptador\n");
				}
			
				
				ImprimirMenu();                             
				break;
				
				
				
			
			case 0x0a: //Això és per enviar els 0x0a (line feed) que s'envia quan li donem al Enter
				break;
			default:
				printf("Opció incorrecta\n");	
				printf("He llegit 0x%hhx \n",input);
				printf("Si us plau seleccioni una opció correcta \n");
				break;
		}

		input = getchar();
	
}
printf("Has sortit del programa\n");
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
