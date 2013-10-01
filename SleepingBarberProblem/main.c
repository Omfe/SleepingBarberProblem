//
//  main.c
//  SleepingBarberProblem
//
//  Created by Omar Gudino on 10/1/13.
//  Copyright (c) 2013 Omar Gudino. All rights reserved.
//

#include <stdio.h>
#include <semaphore.h>

sem_t barber = 0;
sem_t accessWaitingRoom = 1;
sem_t customer = 3;
int numberOfSeatsEmpty = 3;

void Barber()
{
    while (1) {
        printf("I'll sleep until I get waked up\n");
        waitCustomer(1);
        printf("I'm attending a customer\n");
        waitWaitingRoom(1);
        numberOfSeatsEmpty++;
        postBarber(1);
        postWaitingRoom(1);
        printf("I'm cutting your hair!\n");
        sleep(1);
    }
}

void Customer()
{
    while (1) {
        waitWaitingRoom(1);
        if (numberOfSeatsEmpty > 0) {
            printf("I'll wait by sitting down :)\n");
            numberOfSeatsEmpty--;
            postCustomer(1);
            postWaitingRoom(1);
            waitBarber(1);
            printf("I got my haircut neatly!\n");
        }
        else {
            postWaitingRoom(1);
            printf("I wont cut my hair here :@\n");
        }
    }
}

int main(int argc, const char * argv[])
{
    pthread_t barberT, customerT, customerT2, customerT3;
    
    pthread_create(&barberT, NULL, Barber, NULL);
    pthread_create(&customerT, NULL, Customer, NULL);
    pthread_create(&customerT2, NULL, Customer, NULL);
    pthread_create(&customerT3, NULL, Customer, NULL);
    
    pthread_join(barberT, NULL);
    pthread_join(customerT, NULL);
    pthread_join(customerT2, NULL);
    pthread_join(customerT3, NULL);

    
    return 0;
}

sem_t postBarber(int value)
{
    barber = barber + value;
    return barber;
}

sem_t waitBarber(int value)
{
    while (1) {
        if (barber > 0) {
            barber = barber - value;
            break;
        }
    }
    return barber;
}

sem_t postCustomer(int value)
{
    customer = customer + value;
    return customer;
}

sem_t waitCustomer(int value)
{
    while (1) {
        if (customer > 0) {
            customer = customer - value;
            break;
        }
    }
    return customer;
}

sem_t postWaitingRoom(int value)
{
    accessWaitingRoom = accessWaitingRoom + value;
    return accessWaitingRoom;
}

sem_t waitWaitingRoom(int value)
{
    while (1) {
        if (accessWaitingRoom > 0) {
            accessWaitingRoom = accessWaitingRoom - value;
            break;
        }
    }
    return accessWaitingRoom;
}



