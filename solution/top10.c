#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int A[2]; // pipe A
    pipe(A);
    pid_t pid1 = fork(); // cat
    if (!pid1) {
        dup2(A[1], 1);
        close(A[0]);
        close(A[1]);
        execlp("cat","cat", "log.txt", NULL);
        exit(EXIT_FAILURE);
    }
    
    int B[2]; // pipe B
    pipe(B);
    pid_t pid2 = fork();
    if (!pid2) { // cut
        dup2(A[0], 0);
        close(A[0]);
        close(A[1]);
        
        dup2(B[1], 1);
        close(B[0]);
        close(B[1]);
        
        execlp("cut","cut","-f4,7", "-d ", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(A[0]);
    close(A[1]);
    
    int C[2]; // pipe C
    pipe(C);
    
    pid_t pid3 = fork();
    if (!pid3) { // grep
        dup2(B[0], 0);
        close(B[0]);
        close(B[1]);
        
        dup2(C[1], 1);
        close(C[0]);
        close(C[1]);
        
        execlp("grep","grep","28/Oct", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(B[0]);
    close(B[1]);
    
    
    int D[2]; // pipe D
    pipe(D);
    
    pid_t pid4 = fork();
    if (!pid4) { // cut
        dup2(C[0], 0);
        close(C[0]);
        close(C[1]);
        
        dup2(D[1], 1);
        close(D[0]);
        close(D[1]);
        
        execlp("cut","cut", "-f2", "-d ", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(C[0]);
    close(C[1]);
    
    int E[2]; // pipe E
    pipe(E);
    
    pid_t pid5 = fork();
    if (!pid5) { //sort
        dup2(D[0], 0);
        close(D[0]);
        close(D[1]);
        
        dup2(E[1], 1);
        close(E[0]);
        close(E[1]);
        
        execlp("sort","sort", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(D[0]);
    close(D[1]);
    
    int F[2]; // pipe F
    pipe(F);
    
    pid_t pid6 = fork();
    if (!pid6) { // uniq
        dup2(E[0], 0);
        close(E[0]);
        close(E[1]);
        
        dup2(F[1], 1);
        close(F[0]);
        close(F[1]);
        
        execlp("uniq","uniq", "-c", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(E[0]);
    close(E[1]);
    
     int G[2]; // pipe G
    pipe(G);
    
    pid_t pid7 = fork();
    if (!pid7) { //sort
        dup2(F[0], 0);
        close(F[0]);
        close(F[1]);
        
        dup2(G[1], 1);
        close(G[0]);
        close(G[1]);
        
        execlp("sort","sort", "-nr", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(F[0]);
    close(F[1]);

    int H[2]; // pipe H
    pipe(H);
    
    pid_t pid8 = fork();
    if (!pid8) { // cat
        dup2(G[0], 0);
        close(G[0]);
        close(G[1]);
        
        dup2(H[1], 1);
        close(H[0]);
        close(H[1]);
        
        execlp("head", "head",  "-10", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(H[0]);
    close(H[1]);
    
    pid_t pid9 = fork();
    if (!pid9) { 
        dup2(H[0], 0);
        close(H[0]);
        close(H[1]);
        execlp("awk", "awk", "{print $2,\"\",$1,\"---\",1*100/215,\"%\"}", NULL);
        exit(EXIT_FAILURE);
    }
	
   
    close(H[0]);
    close(H[1]);
    waitpid(pid9, 0, 0);
}
