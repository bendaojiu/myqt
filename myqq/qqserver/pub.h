#ifndef PUB_H_
#define PUB_H_

void catch_Signal(int Sign);
int signal1(int signo, void (*func)(int));
void setdaemon();
int socket_create(int port);


#endif /* PUB_H_ */
