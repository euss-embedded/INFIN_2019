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


int main(int argc, char **argv)
{
	struct 		sockaddr_in	serverAddr;
	struct 		sockaddr_in	clientAddr;
	int			sockAddrSize;
	int			sFd;
	int			newFd;
	int			nRead;
	int 		result;
	char		buffer_rebut[256];
	char		buffer_enviat[256];
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
		printf("Connexió acceptada del client: adreça %s, port %d\n",	inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		/*Rebre*/
		result = read(newFd, buffer_rebut, 256);
		printf("Missatge rebut del client(bytes %d): %s\n",	result, buffer_rebut);

		/*Fer procés necessari amb els casos*/
		comunicacio(buffer_rebut, buffer_enviat);

		/*Enviar*/
		result = write(newFd, buffer_enviat, strlen(buffer_enviat)+1); //+1 per enviar el 0 final de cadena
		printf("Missatge enviat a client(bytes %d): %s\n",	result, buffer_enviat);

		/*Tancar el socket fill*/
		if (tancar = 1)
		result = close(newFd);
		
	}
	

	return 0;
}

void comunicacio(char buffer_rebut[256], char buffer_enviat[256], int tancar){
	
	int			v;
	char		temps[2];
	int			num_mostres;
	float		mitjana;
	
	switch (buffer_rebut[1]){
	
		case 'M':
			v = buffer_rebut[2];
			temps[0] = buffer_rebut[3];
			temps[1] = buffer_rebut[4];
			num_mostres = buffer_rebut[5];
			printf("Estat de la maquina (0 = aturar 1 = marxa):%s\n", buffer_rebut[2]);
			printf("Temps de mostreig:%s%s\n", buffer_rebut[3], buffer_rebut[4]);
			printf("Nº de mostres:%s\n", buffer_rebut[5]);
			
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				strcpy(buffer_enviat,"{M1}");
			else if (buffer_rebut[2] > 1 || (buffer_rebut[3] > 2 && buffer_rebut[4] > 0) || buffer_rebut[5] > 9)
				strcpy(buffer_enviat,"{M2}");
			else if (buffer_rebut[2] = 0)
				tancar = 1;
			else
				strcpy(buffer_enviat,"{M0}");
			
		break;
			
		case 'U':
			
			valor_mitjana(num_mostres, mitjana);
			printf("El valor de la mitjana es: %.2f\n", mitjana);
			
			if (buffer_rebut[1] != 'M' && buffer_rebut[1] !='U' && buffer_rebut[1] !='X' && buffer_rebut[1] != 'Y' && buffer_rebut[1] != 'R' && buffer_rebut[1] != 'B' && buffer_rebut[0] != '{' && buffer_rebut[6] != '}')
				strcpy(buffer_enviat,"{U1}");
			else
				strcpy(buffer_enviat[4], mitjana);
				strcpy(buffer_enviat,"{U0}");
		break;
			
		case 'X':
				
			break;
			
		case 'Y':
		
			break;
				
		case 'R':
		
			break;
			
		case 'B':	
		
			break;	

	
}

void valor_mitjana(int num_mostres, float mitjana){

	float num;
	float total_numeros[256];
	int i;
	int j;
	
	for (i=0 ; i<num_mostres ;){
	num = rand () % 21 + 10;
	total_numeros[i]=num;
	i++;
	}

	for (j=0 ; j<num_mostres ;){
	mitjana = mitjana + total_numeros[j];
	j++;
	}
	mitjana = mitjana/num_mostres;
	
	printf("El valor de la mitjana es: %.2f\n", mitjana);
	
	return mitjana;

}

