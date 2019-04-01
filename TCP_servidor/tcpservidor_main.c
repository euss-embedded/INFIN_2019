/*
 * XXXXXX.c
 * 
 * Copyright 2019 INFIN (EUSS) <euss@euss.cat>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

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
#include <string.h>

#define SERVER_PORT_NUM		5001
#define SERVER_MAX_CONNECTIONS	4
#define REQUEST_MSG_SIZE	1024

#define BUFFERRECIVE_TOTAL		12

void comunicacio (char buffer_rebut[], char buffer_enviat[], int tancar);
void missatge (float *mitjana_p, float *maxima_p, float *minima_p, float * contador_p, int num_mostres);

int main(int argc, char **argv){
    
	struct 		sockaddr_in	serverAddr;
	struct 		sockaddr_in	clientAddr;
	int			sockAddrSize;
	int			sFd;
	int			newFd;
	int			nRead;
	int 		result;
	char		buffer_rebut[BUFFERRECIVE_TOTAL];
	char		buffer_enviat[BUFFERRECIVE_TOTAL];
	int			tancar;
	

	/*Preparar l'adreça local*/
	sockAddrSize=sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*Crear un socket*/
	sFd=socket(AF_INET, SOCK_STREAM, 0);
	
	/*Nominalitzar el socket*/
	result = bind(sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	
	/*Crear una cua per les peticions de connexió*/
	result = listen(sFd, SERVER_MAX_CONNECTIONS);
	
	/*Bucle d'acceptació de connexions*/
		while(1){
		printf("\nServidor esperant connexions\n");

		/*Esperar conexió. sFd: socket pare, newFd: socket fill*/
		newFd=accept(sFd, (struct sockaddr *) &clientAddr, &sockAddrSize);
		printf("Connexió acceptada del client: adreça %s, port %d\n",inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		memset( buffer_rebut, 0, BUFFERRECIVE_TOTAL );
		memset( buffer_enviat, 0, BUFFERRECIVE_TOTAL );

		/*Rebre*/
		result = read(newFd, buffer_rebut, BUFFERRECIVE_TOTAL);
		printf("Missatge rebut del client(bytes %d): %s\n",	result, buffer_rebut);

		/*Fer procés necessari amb els casos*/
		
	
	
		comunicacio (buffer_rebut, buffer_enviat, tancar);
		
		
		/*Enviar*/
		result = write(newFd, buffer_enviat, strlen(buffer_enviat)+1); //+1 per enviar el 0 final de cadena
		printf("Missatge enviat a client(bytes %d): %s\n",	result, buffer_enviat);

		/*Tancar el socket fill*/
		if (tancar = 1)
		result = close(newFd);
	}//sortida de while
	

	return 0;
}//sortida del main

void comunicacio(char buffer_rebut[], char buffer_enviat[], int tancar){
	
	//memset(buffer_enviat, '\0', 12);
	//buffer_enviat[12]= '0';
	
	char		temps[2];
	int 		num_mostres;
	float 		mitjana, maxima, minima, contador;

		num_mostres=buffer_rebut[5]-'0';//invertir a un tipo integer
		temps[0] = buffer_rebut[3];//guardar temps
		temps[1] = buffer_rebut[4];
		
	
	switch (buffer_rebut[1]){
		
			
		case 'M':
	
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{M1}");
			else
			
				
				printf("mitjana:%f\n",mitjana);
				printf("maxima_p:%f\n",maxima);
				printf("minima_p:%f\n",minima);
				printf("minima_p:%f\n",contador);
		
				sprintf(buffer_enviat,"{M0}");	
				printf("%s\n", buffer_enviat);
		break;
			
		case 'U':
			
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{U1}");
			else
				
			
				
				missatge(&mitjana, &maxima, &minima, &contador, num_mostres);//llamar funcio m
				sprintf(buffer_enviat,"{U0%2.2f}", mitjana);
				printf("mitjana:%f\n",mitjana);
				printf("maxima_p:%f\n",maxima);
				printf("minima_p:%f\n",minima);
				printf("minima_p:%f\n",contador);			
				
				printf("\n %s",buffer_enviat);
				printf("\n");
		break;
			
		case 'X':
			
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{X1}");
			else
				sprintf(buffer_enviat,"{X0%2.2f}", maxima);
			
				
			break;
			
		case 'Y':
		
			
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{Y1}");
			
			else
				sprintf(buffer_enviat,"{Y0%3.2f}", minima);
				
			break;
				
		case 'R':

		if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{R1}");
			else 
				sprintf(buffer_enviat,"{R0}");
			
			break;
			
		case 'B':	
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				sprintf(buffer_enviat,"{B1}");
			else 
				sprintf(buffer_enviat,"{B0%2.2f}",contador);
		
			break;	

				}
				 //sortida del swtich
	
		
}

void missatge(float *mitjana_p, float *maxima_p, float *minima_p, float *contador_p, int num_mostres){
	
	int i; 
	float num[9], total, maxima1, minima1, mitjana1, contador1;
		
		*contador_p=contador1;
		*maxima_p=maxima1;
		*minima_p=minima1;
		*mitjana_p=mitjana1;
		contador1=5;
		
		for(i=0;i<num_mostres;i++){
			
		num[i] = rand() % 21 + 10;//operacio per fer numeros random
		total+=num[i];	//fer la suma total		
		}	//sortida del for
		
		mitjana1=total/num_mostres;//fer la mitjana 
		maxima1= num[0];
		minima1 = num[0];
	
	for(i=1;i<num_mostres;i++){
		
			if (num[i]> maxima1)
				maxima1=num[i];
			else if (num[i]< minima1)
				minima1=num[i];
	}//sortida del for
		*contador_p=contador1;
		*maxima_p=maxima1;
		*minima_p=minima1;
		*mitjana_p=mitjana1;
}//sortida de la funcio missatge
