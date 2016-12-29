#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
# undef setenv
# if !HAVE_DECL_SETENV
extern int setenv (const char *, const char *, int);
# endif
# define STREQ(a, b) (strcmp (a, b) == 0)
extern char **environ;
int pid;
void pipess();
void myls();
int cd();

void mypath();
char *argv[15];
char *argp[10];
char *argt[10];
int lp;
int countpipe;
FILE *fp;
void file();
char line[1024];
void pipes2();
void pwd();
void exitt();
int main(int argc,char *argz[])
{  while(1)
   {   printf("$ ");
      
         if(fgets(line,sizeof(line),stdin)!=NULL)
          {    
               file();
          }
         
         
         else
          { exit(0);
          }
            
   
           
 }  
 return 0;   
}         

void pipess()      
{    int fds[2][2]; 
     
	int y,z;
	int nop;
	int noc;
       
        nop=2;
        noc=3 ;  
   
  
  
             
      
  for(y=0;y<nop;y++){
	  pipe(fds[y]);
  }

  for(lp=0;lp<noc;lp++){
    if (fork()== 0) {
      if(lp==0){
       close(1);
       dup(fds[lp][1]);
        for(y=0;y<nop;y++){
	 for(z=0;z<2;z++){
	   close(fds[y][z]);
	}
     }
   execvp(*argv,argv);
   perror("failed");
   exit(0);
   }
   else if(lp==noc-1){
    close(0);
    dup(fds[lp-1][0]);
    for(y=0;y<nop;y++)
       for(z=0;z<2;z++)
	 close(fds[y][z]);
    execvp(*argp, argp);
      perror("failed");
    exit(0);
    }
    else{
       close(0);
       dup(fds[lp-1][0]);
       close(1);
       dup(fds[lp][1]);
       for(y=0;y<nop;y++)
       for(z=0;z<2;z++)
	 close(fds[y][z]);
	 execvp(*argt, argt);
	  exit(0);
       }
     }
  }
  for(y=0;y<nop;y++)
	for(z=0;z<2;z++)
		close(fds[y][z]);
  for(y=0;y<noc;y++)
	  wait(0);
 
}
void pipes2()      
{ 
     int fds[1][2];
	int y,z;
	int nop;
	int noc;
        
        nop=1;
        noc=2;  
  
  
  
             
      
  for(y=0;y<nop;y++){
	  pipe(fds[y]);
  }

  for(lp=0;lp<noc;lp++){
    if (fork()== 0) {
      if(lp==0){
       close(1);
       dup(fds[lp][1]);
        for(y=0;y<nop;y++){
	 for(z=0;z<2;z++){
	   close(fds[y][z]);
	}
     }
   execvp(*argv,argv);
   perror("failed");
   exit(0);
   }
   else if(lp==noc-1){
    close(0);
    dup(fds[lp-1][0]);
    for(y=0;y<nop;y++)
       for(z=0;z<2;z++)
	 close(fds[y][z]);
    execvp(*argp, argp);
      perror("failed");
    exit(0);
    }
    else{
       close(0);
       dup(fds[lp-1][0]);
       close(1);
       dup(fds[lp][1]);
       for(y=0;y<nop;y++)
       for(z=0;z<2;z++)
	 close(fds[y][z]);
	 execvp(*argt, argt);
	  exit(0);
       }
     }
  }
  for(y=0;y<nop;y++)
	for(z=0;z<2;z++)
		close(fds[y][z]);
  for(y=0;y<noc;y++)
	  wait(0);
 
}
void file()
{    
        pid_t p;
       
       char *q;
      char *filename,*filename2;
       char *token;
        
          int i=0,j=0,number=0,countgreater = 0,countless = 0,pipecount=0,p1=0,p2=0,p3=0,countio=0,countpipe=0,fd,fd2;
            int err;
    
     
       if ((q = strchr(line,'\n')) != NULL)
                *q = '\0';
      
      while(line[j]!='\0')
      {      if(line[j]=='|')
             { countpipe++;
              j++;
             }
             else if(line[j]=='<' || line[j]=='>')
             {  countio++;
                j++; 
             }
              else
                j++; 
      }
                 
      token = strtok(line," \n");
                                
      if(strcmp(token,"pwd")==0)
      {
          pwd();
      }
      else if(strcmp(token,"exit")==0)
      {  exitt();
      }
      else if(strcmp(token,"cd")==0)
      {
         cd();
      }
      else if(strcmp(token,"set")==0)
      {   mypath();
      }
      
      else if(strcmp(token,"myls")==0)
      {   myls();
      }
      
     else if(countpipe>0)
     {   
             while(token!=NULL)
            { 
                  
             
                    if(strcmp(token,"|") != 0 && pipecount==0)  
                  { argv[p1]=token;
                      
                    p1++;
                  }  
                 if(strcmp(token,"|") != 0 && pipecount==1 && countpipe==2)
                 {  
                     argt[p2]=token;
                   
                    p2++;
                 }
                  if((strcmp(token,"|") != 0 && pipecount==2)||((strcmp(token,"|")!=0) && pipecount==1 && countpipe==1))
                 {  argp[p3]=token;
                    
                    p3++;
                 }
                    
                 token = strtok(NULL," \n");
               
                 if(token!=NULL && strcmp(token,"|") == 0)
                 {  
                    pipecount++;
                   
                 }
              }  
             
                argv[p1]=NULL;
                 argt[p2]=NULL;
                 argp[p3]=NULL;
        if(countpipe==2)       
        pipess();
        if(countpipe==1)
        pipes2();
  }   


    

       else if(countpipe==0)
       {
             while(token!=NULL)
         {  
            
       
             if((number==1) && ((strcmp(token,">") == 0) || strcmp(token,"<") == 0))
            {    if(strcmp(token,">")==0)
                 countgreater++;
                 if(strcmp(token,"<")==0)
                 countless++; 
                 token=strtok(NULL," \n");
                 filename2=(char*)malloc(sizeof(strlen(token))+1);
                 if(token!=NULL && strcmp(token,">")!=0) 
                 strcpy(filename2,token);  
                 printf("%s\n",filename2);  
            }

            else if((number==0) && ((strcmp(token,">") == 0) || strcmp(token,"<") == 0))
            {   if(strcmp(token,"<")==0)
                countless++;
                if(strcmp(token,">")==0)
                countgreater++;
                token=strtok(NULL," \n");
                 if(token!=NULL) 
		 {filename =(char*)malloc(sizeof(strlen(token))+1);
                  strcpy(filename,token);
                  number++;
                 } 
            }
            
            else
            {     argv[i]=token;
                  
                     i++;
            } 
                 token=strtok(NULL," \n");   
        }       
               argv[i]=NULL;
              
          p=fork();
          if(p==-1)
          {  perror("failed");
              exit(1);
          }
               
           if(p==0)
          {    if(countgreater==1 && countless==0)
              {  fd=open(filename,O_CREAT | O_RDWR | O_TRUNC,0777);
                 close(STDOUT_FILENO);
                 dup(fd);
                 close(fd);
               }
               if(countgreater==0 && countless==1)
               {  
                   fd=open(filename,O_CREAT | O_RDWR,0777);
                   close(STDIN_FILENO);
                   dup(fd);
                   close(fd);
               }
               if(countgreater==1 && countless==1)   
               {   fd=open(filename,O_CREAT | O_RDWR,0777);
                   close(STDIN_FILENO);
                   dup(fd);
                   close(fd);
                   fd2=open(filename2,O_CREAT | O_RDWR |O_TRUNC,0777);
                   close(STDOUT_FILENO);
                   dup(fd2);
                   close(fd2);
                }
                      
        
             
                err=execvp(*argv,argv);
                if(err==-1)
                printf("error");
           }    
                
           else
           {  wait(NULL);
             
           }
       
           
}
 else
 perror("failed"); 
}
void pwd()
{
   char *p;
      p=getenv("PWD");
      printf("%s",p);
      
}
void exitt()
{
   exit(0);
}
      
void mypath() 
{     int i;
       char *z;
       char *y;
       char *x; 
       z=strtok(NULL," ");
       y=strtok(NULL," ");
       if(strcmp(y,"=")==0)
       x=strtok(NULL," ");
       i=setenv(z,x,1);
       if(i!=0)
       perror("failed");
       

 
}
void myls()
{ pid_t p;
    char *argk[64];
     int k=0;
     char buff[1024];
     char *z;
     z=getenv("MYPATH");
    if(z!=NULL) 
    { 
      strcpy(buff,z);
      while(buff[k]!='\0')
      {   if(buff[k]==':')
           buff[k]='\0';
           k++;
      }
          strcat(buff,"/myls");
       
    

      argk[0]=buff;
      argk[1]=NULL;
     
       p=fork();
      if(p==0)  
      { 
        execv(*argk,argk); 
        perror("failed");
         printf("hello");        

     }
      else
      {
          wait(NULL);
        
      }
    }
     else
     perror("failed");   
}

int cd()
{      char *z;
       char *q;
       int c;
       char *p;
        
       char old[100];
       z=strtok(NULL," ");
       p=getenv("PWD");
       strcpy(old,p);
    if(z!=NULL)
   {   if(strcmp(z,"/")!=0 && z[0]!='/' && strcmp(z,"..")!=0 && strcmp(z,".")!=0)  
     {  if(strcmp(old,"/")!=0)
        { strcat(p,"/");
         strcat(p,z);
         c=chdir(p);
        
        }    
        else if(strcmp(old,"/")==0)
         {  strcat(p,z);
             c=chdir(p);
         }    
         
        if(c==0)
        {
        
         setenv("PWD",p,1);
         setenv("OLDPWD",old,1);
        } 
      
      
          else
          { perror("failed");
            setenv("PWD",old,1);
          } 
     } 
      else if(strcmp(z,"/")==0)
      {   c= chdir(z);
          printf("%d",c);
         if(c==0)
        {
         setenv("PWD",z,1);
         setenv("OLDPWD",old,1);
         
         
        }
          
      }
      else if(z[0]=='/' && strcmp(z,"/")!=0)
      {
         c=chdir(z);
         if(c==0)
        {  
          setenv("PWD",z,1);
          setenv("OLDPWD",old,1);
        }
     }
      else if(strcmp(z,"..")==0)
      {     
         q=strrchr(p,'/');
          *q='\0';
           c=chdir(p);
           if(c==0)
           {
               
               setenv("PWD",p,1);
               setenv("OLDPWD",old,1);
           }
           if(c!=0)
           {       c=chdir("/"); 
                   setenv("PWD","/",1);
                   setenv("OLDPWD",old,1);
           }
      }  
       else
      perror("failed");
}       
     return 0;  
}

